#pragma once

#include "Entity.h"
#include "String.hpp"
#include "Animation.h"

class Player : public Entity {
public:
  enum State { IDLE, WALKING, JUMP, ALL };

  Player(int x, int y, unsigned int exp) : Entity(x, y, 100, exp) {}
  Player() : Entity(0, 0, 100, 0) {}
  virtual ~Player() {}

  void DrawHealth(se::Window &window) const {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.0f, (float)window.GetHeight(), 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(15);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    int points = GetHealth()/1.25;
    for (int i = 0; i < points; i++) {
      glVertex2f(190*cosf((275+i)*3.14/180), 190*sinf((275+i)*3.14/180));
    }
    glEnd();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
  }

  virtual void Tick(std::vector<PhysicsObject *> things) override {
    SetColor(se::Color());
    if (!damage.CheckEffect() && !freeze.CheckEffect() && !stun.CheckEffect()) {
      lastEffect = nullptr;
    }
    else
      SetColor(lastEffect->GetColor());
    animation[state].SetX(GetX());
    animation[state].SetY(GetY()-5);
    animation[state].FlipX(IsFlippedX());
    Entity::Tick(things);
  }

  Animation animation[ALL];
  State state;
};