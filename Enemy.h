#pragma once

#include "Font.h"
#include "DrawSomeTime.h"
#include "String.hpp"
#include "Entity.h"
#include "Window.hpp"
#include "Player.h"

#include <vector>

extern std::vector<DrawSomeTime<se::String>> damageString;
extern se::Font *font;
extern Player player;

class Enemy : public Entity {
public:
  Enemy(int x, int y)
    : Entity(x, y), moveSpeed(3), attackSpeed(3)
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
    if (!damage.CheckEffect() && !freeze.CheckEffect() && !stun.CheckEffect())
      lastEffect = nullptr;
    else
      SetColor(lastEffect->GetColor());

    if (!stun.UnderEffect()) {
      // Here AI!
      int move = freeze.UnderEffect() ? moveSpeed/2 : moveSpeed;
      int px = player.GetX();
      if (px < GetX()) {
        this->Move(-move, 0);
        this->FlipX(true);
      }
      else if (px > GetX()) {
        this->Move(move, 0);
        this->FlipX(false);
      }
    }
    
    if (CheckCollision(&player)) {
      player.DamageHim(5);
    }

    Tick(floors);
  }

  int moveSpeed;
  int attackSpeed;
};