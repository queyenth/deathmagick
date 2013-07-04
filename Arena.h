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
se::Sprite stair(880, window.GetHeight()/4);
se::Image stairImage;
int stairHeight;
int angles[3];
se::Sprite clouds[30];
se::Image cloudImage;
std::vector<std::shared_ptr<Skill>> skillsOnFrame;
bool moved = false;
se::Image interfaceImg;
se::Sprite interfaceS;

void InitStairs() {
  //stairImage.LoadFromFile("img\\stair.png");
  //stair.SetImage(stairImage);
  //stairHeight = floors[2].GetY()+floors[2].GetHeight()+10-window.GetHeight()/4;
}

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
  FILE *file = fopen("test.txt", "r");
  int k1,k2,k3;
  fscanf(file, "%d %d %d", &k1, &k2, &k3);
  fclose(file);
  imprs.push_back(tagIMPR(k1, k2, k3));
}

void InitArena() {
  ShowCursor(FALSE);
  LevelLoader loader;
  loader.LoadLevel("first", player, floors, enemies);
  InitBackgrounds();
  InitStairs();
  InitSpheres();
  InitImprs();
}

void DeinitArena() {
  enemies.clear();
  damageString.clear();
  for (auto i = floors.begin(); i != floors.end(); i++)
    delete *i;
}

void DrawHealth() {
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(0.0f, window.GetHeight(), 0.0f);
  glColor3f(1.0f, 0.0f, 0.0f);
  glPointSize(10);
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_POINT_SMOOTH);
  glBegin(GL_POINTS);
  // 80 точек
  // здоровье = 100 поинтов
  // одна точка = 100/80 = 1,25 поинтов
  // кол-во точек = здоровье/1.25, если здоровье = 100, то точек = 80
  int points = (int)player.GetHealth()/1.25;
  for (int i = 0; i < points; i++) {
    glVertex2f(190*cos((275+i)*3.14/180), 190*sin((275+i)*3.14/180));
  }
  glEnd();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
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
  else if (input.IsKeyPressed('S')) {
    if (player.inAir == Player::ONSTAIR)
      player.Move(0, -3);
  }
  if (input.IsKeyPressed('A')) {
    player.TryToMove(-1, 0, floors);
    destination = LEFT;
    moved = true;
    player.FlipX(true);
  }
  else if (input.IsKeyPressed('D')) {
    player.TryToMove(1, 0, floors);
    destination = RIGHT;
    moved = true;
    player.FlipX(false);
  }

  int middle = window.GetWidth()/3 + camera.GetViewX();
  if (player.GetX() <= window.GetWidth()/3)
    camera.SetViewPoint(se::Vertex2D(0, 0));
  else if (moved) {
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

  damageString.erase(std::remove_if(damageString.begin(), damageString.end(), [](DrawSomeTime<se::String> t) { return GetTickCount() - t.firstTime > t.time; }), damageString.end());
  effects.erase(std::remove_if(effects.begin(), effects.end(), [](DrawSomeTime<Entity> t) { return GetTickCount() - t.firstTime > t.time; }), effects.end());
  skillsOnFrame.erase(std::remove_if(skillsOnFrame.begin(), skillsOnFrame.end(), [](std::shared_ptr<Skill> t) { return !t->casting; }), skillsOnFrame.end());

  int countOfDied = 0;
  enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&countOfDied](Enemy t) -> bool { if (!t.IsAlive()) countOfDied++; return !t.IsAlive(); }), enemies.end());
  player.experience += countOfDied*12;
  
  for (auto i = enemies.begin(); i != enemies.end(); i++) {
    i->AITick(floors);
  }

  window.Clear(se::Color(0.258f, 0.66f, 1.0f));

  if (!player.IsAlive())
    currentState = ARENA_DEINIT;
  
  // Drawing background
  for (int i = 0; i < 30; i++)
    window.Draw(&clouds[i]);

  // Drawing interface
  window.Draw(&interfaceS);

  // Drawing healthbar
  DrawHealth();

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
          j->DamageHim(12);
      window.Draw(i->entity.get());
    }


  window.Display();

  // For 60 FPS
  Sleep(15);
}