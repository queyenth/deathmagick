#pragma once

#include "GlobalObject.h"
#include "Line.h"
#include "Meteor.h"

#include <algorithm>

enum Destination { LEFT, RIGHT };

int backgroundScroll1;
int backgroundScroll2;
se::Image playerImg;
Player player;
vector<Player> enemies;
se::Sprite spheres[3];
bool k1p, k2p, k3p;
bool castingSkill = false;
KeySphere currentSphere;
std::vector<PhysicsObject *> floors;
se::Sprite stair(880, window.GetHeight()/4);
se::Image stairImage;
se::Sprite health(0, window.GetHeight()-10, player.GetHealth(), 10, se::Color(0.8f, 0.2f, 0.2f), true);
int stairHeight;
std::vector<DrawSomeTime> damageString;
se::Sprite backgrounds[2];
se::Image backgroundImage;
int destination = RIGHT;
bool moved = false;

void InitEnemies() {
  playerImg.LoadFromFile("img\\player.png");
  for (int i = 0; i < 10; i++) {
    Player enemy;
    enemy.SetX((i+1)*300);
    enemy.SetImage(playerImg);
    enemy.SetY(window.GetHeight()/2);
    enemies.push_back(enemy);
  }
}

void InitPlayer() {
  playerImg.LoadFromFile("img\\player.png");
  player.SetImage(playerImg);
  player.SetX(5);
  player.SetY(window.GetHeight()/3);
  player.health = 100;
  player.experience = 0;
}

void InitStairs() {
  //stairImage.LoadFromFile("img\\stair.png");
  //stair.SetImage(stairImage);
  //stairHeight = floors[2].GetY()+floors[2].GetHeight()+10-window.GetHeight()/4;
}

void InitBackgrounds() {
  backgroundImage.LoadFromFile("img\\arena_back.png");
  for (int i = 0; i < 2; i++) {
    backgrounds[i].SetImage(backgroundImage);
    backgrounds[i].SetWidth(window.GetWidth());
    backgrounds[i].SetHeight(window.GetHeight());
    backgrounds[i].SetFixedMode(true);
  }
  backgrounds[1].SetX(window.GetWidth());
  backgroundScroll1 = 0;
  backgroundScroll2 = window.GetWidth();
}

void InitFloors() {
  floors.push_back(new se::Line(0, 4000, window.GetHeight()/4-50));
}

void InitSpheres() {
  for (int i = 0; i < 3; i++) {
    spheres[i].SetY(window.GetHeight()-60);
    spheres[i].SetFixedMode(true);
  }
  sphereImages[0].LoadFromFile("img\\f1.png");
  sphereImages[1].LoadFromFile("img\\l1.png");
  sphereImages[2].LoadFromFile("img\\m1.png");
  k1p = k2p = k3p = false;
}

void InitSkills() {
  // Meteor
  skills.first = KeySphere(2, 1, 0);
  skills.second = new Meteor();
}

void DeinitSkills() {
  delete skills.second;
}

void InitArena() {
  ShowCursor(FALSE);
  InitBackgrounds();
  InitFloors();
  InitStairs();
  InitPlayer();
  InitEnemies();
  InitSpheres();
  InitSkills();
}

void DeinitArena() {
  enemies.clear();
  damageString.clear();
  DeinitSkills();
  for (auto i = floors.begin(); i != floors.end(); i++)
    delete *i;
}

void DrawArena() {

  int castType = 0;

  // Handle keys here
  if (currentSphere.IsFull()) {
    if (input.IsKeyPressed(VK_SPACE))
      castingSkill = true;
  }
  else {
    if (input.IsKeyPressed(49) && !k1p) { currentSphere.k1++; castType = 1; k1p = true; }
    else if (input.IsKeyPressed(50) && !k2p) { currentSphere.k2++; castType = 2; k2p = true; }
    else if (input.IsKeyPressed(51) && !k3p) { currentSphere.k3++; castType = 3; k3p = true;}
    
    if (!input.IsKeyPressed(49)) k1p = false;
    if (!input.IsKeyPressed(50)) k2p = false;
    if (!input.IsKeyPressed(51)) k3p = false;
  }
  
  if (input.IsKeyPressed(VK_ESCAPE)) {
    currentState = GAME_MENU;
    return;
  }

  if (input.IsKeyPressed('W')) {
    if (stair.GetX() <= player.GetX() && player.GetX() <= stair.GetX() + stair.GetWidth()
        && stair.GetY()-stairHeight <= player.GetY() && player.GetY() <= stair.GetY()) {
      player.inAir = Player::ONSTAIR;
    }
    else if (player.inAir == Player::ONSTAIR) {
      player.inAir = Player::STADING;
    }
    if (player.inAir == Player::ONSTAIR)
      player.Move(0, 3);
    else
      player.Jump();
  }
  if (input.IsKeyPressed('A')) {
    player.TryToMove(-3, 0, floors);
    destination = LEFT;
    moved = true;
    player.FlipX(true);
  }
  if (input.IsKeyPressed('D')) {
    player.TryToMove(3, 0, floors);
    destination = RIGHT;
    moved = true;
    player.FlipX(false);
  }
  if (input.IsKeyPressed('S')) {
    if (player.inAir == Player::ONSTAIR)
      player.Move(0, -3);
  }

  int middle = window.GetWidth()/3 + camera.GetViewX();
  if (player.GetX() <= window.GetWidth()/3)
    camera.SetViewPoint(se::Vertex2D(0, 0));
  else if (moved) {
    camera.OffsetViewByX(player.GetX() - middle);
    if (destination == LEFT) {
      backgroundScroll1++;
      backgroundScroll2++;
      if (backgroundScroll1 > window.GetWidth()) {
        backgroundScroll1 = -window.GetWidth();
      }
      if (backgroundScroll2 > window.GetWidth()) {
        backgroundScroll2 = -window.GetWidth();
      }

      backgrounds[0].SetX(backgroundScroll1);
      backgrounds[1].SetX(backgroundScroll2);
    }
    else {
      backgroundScroll1--;
      backgroundScroll2--;
      if (backgroundScroll1 < -window.GetWidth()) {
        backgroundScroll1 = window.GetWidth();
      }
      if (backgroundScroll2 < -window.GetWidth()) {
        backgroundScroll2 = window.GetWidth();
      }

      backgrounds[0].SetX(backgroundScroll1);
      backgrounds[1].SetX(backgroundScroll2);
    }
    moved = false;
  }
  
  // Key-hack for testing
  if (input.IsKeyPressed(VK_F1)) { currentSphere.k1 = 2; currentSphere.k2 = 1; currentSphere.k3 = 0; castingSkill = true; };
  
  if (castType != 0) {
    int count = currentSphere.GetCount()-1;
    spheres[count].SetImage(sphereImages[castType-1]);
    spheres[count].SetX(50*count);
  }
  
  player.Tick(floors);
  health.SetWidth(player.GetHealth()*2);

  // TODO : Erase all dead enemies from vector [amazing stuff, but I think that it costs a lot of time]
  // TODO : Will check it later.

  int countOfDied = 0;
  enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&countOfDied](Player t) -> bool { if (!t.IsAlive()) countOfDied++; return !t.IsAlive(); }), enemies.end());
  damageString.erase(std::remove_if(damageString.begin(), damageString.end(), [](DrawSomeTime t) { return GetTickCount() - t.firstTime > t.time; }), damageString.end());
  player.experience += countOfDied*12;
  
  for (auto i = enemies.begin(); i != enemies.end(); i++) {
    //i->AITick(floors);
    i->Tick(floors);
    if (GetTickCount() - i->damageTime > 2000 && i->damageTime != 0) {
      i->damageTime = 0;
      i->SetColor(se::Color());
    }
  }

  window.Clear(se::Color(0.0f, 0.0f, 0.0f));

  if (!player.IsAlive())
    currentState = ARENA_DEINIT;
  
  // Drawing background
  for (int i = 0; i < 2; i++)
    window.Draw(&backgrounds[i]);

  // Drawing floor
  for (auto i = floors.begin(); i != floors.end(); i++)
    window.Draw(*i);
  
  // Drawing stairs
  /*for (int i = 0; i <= stairHeight; i+=10) {
    stair.SetY(window.GetHeight()/4+i);
    window.Draw(&stair);
  }*/

  // Drawing player
  window.Draw(&player);

  // Drawing enemies
  for (auto i = enemies.begin(); i != enemies.end(); i++) {
	  window.Draw(&*i);
    i->DrawHealth(window);
  }
    
  // Drawing spheres
  for (int i = 0; i < currentSphere.GetCount(); i++)
    window.Draw(&spheres[i]);
    
  // Drawing health bar
  window.Draw(&health);

  // Drawing skill
  if (castingSkill) {
    if (skills.first == currentSphere) {
      skills.second->Cast(player);
    }
    currentSphere.Clear();
    castingSkill = false;
  }

  // If skill casting draw skill, and check on collision
  if (skills.second->casting) {
    skills.second->Tick(window, floors);
    if (!skills.second->casting) {
      int left = skills.second->GetX() - skills.second->GetRange();
      if (left <= 0) left = 0;
      int right = skills.second->GetX() + skills.second->GetWidth() + skills.second->GetRange();
      for (auto it = enemies.begin(); it != enemies.end(); it++) {
        if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right) {
          wchar_t text[5];
          wsprintf(text, L"%d", skills.second->GetDamage());
          damageString.push_back(DrawSomeTime(std::make_shared<se::String>(se::String(text, font, it->GetX()+it->GetWidth()+2, it->GetY()+it->GetHeight(), se::Color(1.0f, 1.0f, 1.0f), false)), 1000));
          it->DamageHim(skills.second->GetDamage());
        }
      }
    }
  }

  for (auto i = damageString.begin(); i != damageString.end(); i++)
    if (i->entity != nullptr)
      window.Draw(i->entity.get());
  
  window.Display();

  // For 60 FPS
  Sleep(15);
}