#pragma once

#include "GlobalObject.h"
#include "Line.h"
#include "SkillFactory.h"

#include <algorithm>

enum Destination { LEFT, RIGHT };

int backgroundScroll1;
int backgroundScroll2;
Destination destination;
se::Image playerImg;
se::Sprite spheres[3];
bool k1p, k2p, k3p;
bool castingSkill = false;
KeySphere currentSphere;
se::Sprite stair(880, window.GetHeight()/4);
se::Image stairImage;
se::Sprite health(0, window.GetHeight()-10, player.GetHealth(), 10, se::Color(0.8f, 0.2f, 0.2f), true);
int stairHeight;
se::Sprite backgrounds[2];
se::Image backgroundImage;
std::vector<std::shared_ptr<Skill>> skillsOnFrame;
bool moved = false;

void InitEnemies() {
  playerImg.LoadFromFile("img\\player.png");
  for (int i = 0; i < 10; i++) {
    Enemy enemy;
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
  player.speed = 3;
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

void InitImprs() {
  FILE *file = fopen("test.txt", "r");
  int k1,k2,k3;
  fscanf(file, "%d %d %d", &k1, &k2, &k3);
  fclose(file);
  imprs.push_back(tagIMPR(k1, k2, k3));
}

void InitArena() {
  ShowCursor(FALSE);
  InitBackgrounds();
  InitFloors();
  InitStairs();
  InitPlayer();
  InitEnemies();
  InitSpheres();
  InitImprs();
}

void DeinitArena() {
  enemies.clear();
  damageString.clear();
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
    player.TryToMove(-1, 0, floors);
    destination = LEFT;
    moved = true;
    player.FlipX(true);
  }
  if (input.IsKeyPressed('D')) {
    player.TryToMove(1, 0, floors);
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

  int countOfDied = 0;
  enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&countOfDied](Enemy t) -> bool { if (!t.IsAlive()) countOfDied++; return !t.IsAlive(); }), enemies.end());
  damageString.erase(std::remove_if(damageString.begin(), damageString.end(), [](DrawSomeTime t) { return GetTickCount() - t.firstTime > t.time; }), damageString.end());
  skillsOnFrame.erase(std::remove_if(skillsOnFrame.begin(), skillsOnFrame.end(), [](std::shared_ptr<Skill> t) { return !t->casting; }), skillsOnFrame.end());
  player.experience += countOfDied*12;
  
  for (auto i = enemies.begin(); i != enemies.end(); i++) {
    i->AITick(floors);
    //i->Tick(floors);
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
    skillsOnFrame.push_back(SkillFactory::MakeSkill(currentSphere, imprs[0]));
    skillsOnFrame[skillsOnFrame.size()-1]->Cast(player);
    currentSphere.Clear();
    castingSkill = false;
  }

  // If skill casting draw skill, and check on collision
  for (auto i = skillsOnFrame.begin(); i != skillsOnFrame.end(); i++)
    (*i)->casting = (*i)->operation();

  for (auto i = damageString.begin(); i != damageString.end(); i++)
    if (i->entity != nullptr)
      window.Draw(i->entity.get());
  
  window.Display();

  // For 60 FPS
  Sleep(15);
}