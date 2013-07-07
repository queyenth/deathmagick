#pragma once

#include "Font.h"
#include "DrawSomeTime.h"
#include "String.hpp"
#include "Entity.h"
#include "Window.hpp"

#include <vector>

extern std::vector<DrawSomeTime<se::String>> damageString;
extern se::Font *font;

class Enemy : public Entity {
public:
  Enemy(int x, int y)
    : Entity(x, y)
  {}
  Enemy() : Entity(0, 0)
  {}
  virtual ~Enemy() {}

  void DrawHealth(se::Window &window) const override {
    int width = GetHealth() * GetWidth()/100;
    se::Sprite health(GetX(), GetY()+GetHeight()+5, width, 5, se::Color(0.8f, 0.2f, 0.2f), false);
    window.Draw(&health);
  }

  // We need make AI FUCKING AWESOME
  void AITick(std::vector<PhysicsObject *> floors) {
    SetColor(se::Color());
    if (!damage.CheckEffect() && !freeze.CheckEffect() && !stun.CheckEffect()) {
      lastEffect = nullptr;
    }
    else
      SetColor(lastEffect->GetColor());
    Tick(floors);
  }

  int moveSpeed;
  int attackSpeed;
};