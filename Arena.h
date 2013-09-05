#pragma once

#include "GlobalObject.h"
#include "Line.h"
#include "SkillFactory.h"
#include "LevelLoader.h"

#include <algorithm>

enum Destination { LEFT, RIGHT };

Destination destination;
se::Image playerImg;
se::Sprite spheres[3];
bool k1p, k2p, k3p;
bool castingSkill = false;
KeySphere currentSphere;
int angles[3];
se::Sprite clouds[30];
se::Image cloudImage;
std::vector<std::shared_ptr<Skill>> skillsOnFrame;
bool moved = false;
se::Image interfaceImg;
se::Sprite interfaceS;

void InitBackgrounds() {
  cloudImage.LoadFromFile("img\\cloud.png");
  for (int i = 0; i < 30; i++) {
    //srand(GetTickCount());
    clouds[i].SetImage(cloudImage);
    clouds[i].SetFixedMode(true);
    clouds[i].SetX(rand()%3200);
    clouds[i].SetY(rand()%window.GetHeight());
    clouds[i].SetFixedMode(true);
  }
  interfaceImg.LoadFromFile("img\\interface.png");
  interfaceS = se::Sprite(0, window.GetHeight()-200);
  interfaceS.SetImage(interfaceImg);
  interfaceS.SetFixedMode(true);
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
  angles[0] = angles[1] = angles[2] = 0;
}

void InitImprs() {
  FILE *file;
  fopen_s(&file, "test.txt", "r");
  int k1,k2,k3;
  fscanf_s(file, "%d %d %d", &k1, &k2, &k3);
  fclose(file);
  imprs.push_back(tagIMPR(k1, k2, k3));
}

void InitArena() {
  ShowCursor(FALSE);
  LevelLoader loader;
  loader.LoadLevel("first");
  player.SetHealth(100);
  player.experience = 0;
  player.animation[Player::IDLE].AddFrame("img\\Player3.png");
  player.animation[Player::IDLE].SetLoop(true);

  player.animation[Player::WALKING].AddFrame("img\\Player1.png");
  player.animation[Player::WALKING].AddFrame("img\\Player0.png");
  player.animation[Player::WALKING].AddFrame("img\\Player2.png");
  player.animation[Player::WALKING].AddFrame("img\\Player0.png");
  player.animation[Player::WALKING].SetSpeed(100);
  player.animation[Player::WALKING].SetLoop(true);

  InitBackgrounds();
  stairImg.LoadFromFile("img\\stair.png");
  tableImg.LoadFromFile("img\\table.png");
  InitSpheres();
  InitImprs();
  camera.OffsetViewByX(player.GetX() - window.GetWidth()/3);
}

void DeinitArena() {
  enemies.clear();
  damageString.clear();
  skillsOnFrame.clear();
  for (auto i = floors.begin(); i != floors.end(); i++)
    delete *i;
  floors.clear();
}

void UpdateAll() {
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

  bool onStair = false;
  if (input.IsKeyPressed('W')) {
    for (auto i = stairs.begin(); i != stairs.end(); i++) {
      if (i->x-15 <= player.GetX() && player.GetX() <= i->x+15
      && i->startY <= player.GetY() && player.GetY() <= i->startY+i->count*10) {
        onStair = true;
        player.Move(0, 3);
        player.inAir = Player::ONSTAIR;
        break;
      }
    }
    if (!onStair) {
      if (player.inAir == Player::ONSTAIR) {
        player.inAir = Player::STADING;
      }
      else {
        player.Jump();
      }
    }
  }
  else if (input.IsKeyPressed('S')) {
    for (auto i = stairs.begin(); i != stairs.end(); i++) {
      if (i->x-15 <= player.GetX() && player.GetX() <= i->x+15
      && i->startY <= player.GetY() && player.GetY() <= i->startY+i->count*10) {
        onStair = true;
        player.Move(0, -3);
        player.inAir = Player::ONSTAIR;
        break;
      }
    }
  }

  if (input.IsKeyPressed('A')) {
    if (player.TryToMove(-1, 0, floors)) {
      destination = LEFT;
      moved = true;
      player.FlipX(true);
    }
  }
  else if (input.IsKeyPressed('D')) {
    if (player.TryToMove(1, 0, floors)) {
      destination = RIGHT;
      moved = true;
      player.FlipX(false);
    }
  }

  if (!moved) {
    if (player.inAir == Player::ONSTAIR)
      player.inAir = Player::STADING;
    player.state = Player::IDLE;
    player.animation[Player::WALKING].SetCurrentFrame(0);
  }

  int middle = window.GetWidth()/3 + camera.GetViewX();
  if (player.GetX() <= window.GetWidth()/3) {
    camera.SetViewPoint(se::Vertex2D(0, 0));
    if (moved) {
      player.state = Player::WALKING;
      moved = false;
    }
  }
  else if (moved) {
    player.state = Player::WALKING;
    camera.OffsetViewByX(player.GetX() - middle);
    if (destination == LEFT) {
      for (int i = 0; i < 30; i++)
        clouds[i].Move(1, 0);
    }
    else {
      for (int i = 0; i < 30; i++)
        clouds[i].Move(-1, 0);
    }
    moved = false;
  }
  
  // Key-hack for testing
  if (input.IsKeyPressed(VK_F1)) { currentSphere.k1 = 2; currentSphere.k2 = 1; currentSphere.k3 = 0; castingSkill = true; };
  
  if (castType != 0) {
    int count = currentSphere.GetCount()-1;
    spheres[count].SetImage(sphereImages[castType-1]);
    if (count == 0)
      angles[0] = 0;
    else
      angles[count] = angles[count-1]+120;
  }
  
  player.Tick(floors);
  if (!player.IsAlive())
    currentState = ARENA_DEINIT;

  damageString.erase(std::remove_if(damageString.begin(), damageString.end(), [](DrawSomeTime<se::String> t) { return GetTickCount() - t.firstTime > t.time; }), damageString.end());
  effects.erase(std::remove_if(effects.begin(), effects.end(), [](DrawSomeTime<Entity> t) { return GetTickCount() - t.firstTime > t.time; }), effects.end());
  skillsOnFrame.erase(std::remove_if(skillsOnFrame.begin(), skillsOnFrame.end(), [](std::shared_ptr<Skill> t) { return !t->casting; }), skillsOnFrame.end());

  int countOfDied = 0;
  enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&countOfDied](Enemy t) -> bool { if (!t.IsAlive()) countOfDied++; return !t.IsAlive(); }), enemies.end());
  player.experience += countOfDied*12;
  
  for (auto i = enemies.begin(); i != enemies.end(); i++) {
    i->AITick(floors);
  }
}

void DisplayAll() {
  window.Clear(se::Color(0.258f, 0.66f, 1.0f));
  
  // Drawing background
  for (int i = 0; i < 30; i++)
    window.Draw(&clouds[i]);

  // Drawing interface
  window.Draw(&interfaceS);

  // Drawing healthbar
  player.DrawHealth(window);

  // Drawing floor
  for (auto i = floors.begin(); i != floors.end(); i++)
    window.Draw(*i);
  
  // Drawing stairs
  
  for (auto i = stairs.begin(); i != stairs.end(); i++) {
    se::Sprite stair(i->x);
    stair.SetImage(stairImg);
    for (int j = 0; j < i->count; j++) {
      stair.SetY(i->startY+j*10);
      window.Draw(&stair);
    }
  }

  // Drawing runes
  for (auto i = runes.begin(); i != runes.end(); i++)
    window.Draw(&*i);

  // Drawing player
  window.Draw(&player.animation[player.state]);

  // Drawing enemies
  for (auto i = enemies.begin(); i != enemies.end(); i++) {
    window.Draw(&*i);
    i->DrawHealth(window);
  }
    
  // Drawing spheres
  for (int i = 0; i < currentSphere.GetCount(); i++) {
    spheres[i].SetX(57+45*cos(angles[i]*3.14/180));
    spheres[i].SetY(window.GetHeight()-95+45*sin(angles[i]*3.14/180));
    angles[i]-=2;
    window.Draw(&spheres[i]);
  }

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
  
  for (auto i = effects.begin(); i != effects.end(); i++)
    if (i->entity != nullptr) {
      for (auto j = enemies.begin(); j != enemies.end(); j++)
        if (j->CheckCollision(i->entity.get()))
          j->DamageHim(Damage(Damage::PHYSICAL, 12));
      window.Draw(i->entity.get());
    }

  window.Display();
}

DWORD beginTime;
DWORD timeDiff;
int sleepTime;
int framesSkipped;

void DrawArena() {
  static const int MAX_FPS = 60;
  static const int MAX_FRAME_SKIPS = 5;
  static const int FRAME_PERIOD = 1000 / MAX_FPS;
  
  while (currentState == ARENA_PLAY) {
    window.ProcessEvents();

    beginTime = GetTickCount();
    framesSkipped = 0;
    UpdateAll();
    DisplayAll();
    timeDiff = GetTickCount() - beginTime;
    sleepTime = FRAME_PERIOD - timeDiff;
    if (sleepTime > 0) {
      Sleep(sleepTime);
    }
    while (sleepTime < 0 && framesSkipped < MAX_FRAME_SKIPS) {
      UpdateAll();
      sleepTime += FRAME_PERIOD;
      framesSkipped++;
    }
  }
}