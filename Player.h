#pragma once

#include "PhysicsObject.h"
#include "String.hpp"

class Player : public PhysicsObject {
public:
  Player(int x, int y, unsigned int exp) : PhysicsObject(x, y), experience(exp), health(100), damageTime(0) {}
  Player() : PhysicsObject(0, 0), experience(0), health(100), damageTime(0) {}
  virtual ~Player() {}
  void Jump() {
    if (inAir != STADING) return;
    inAir = INAIR;
    currentJump = maxJump;
  }

  void DamageHim(int damage) {
	  if (health - damage <= 0)
      health = 0;
	  else
	    health -= damage;
    SetColor(se::Color(1.0f, 0.4f, 0.4f, 1.0f));
    damageTime = GetTickCount();
  }

  bool IsAlive() const {
    return health != 0;
  }

  int GetHealth() const {
    return health;
  }

  void DrawHealth(se::Window &window) const {
    int width = GetHealth() * GetWidth()/100;
    se::Sprite health(GetX(), GetY()+GetHeight()+5, width, 5, se::Color(0.8f, 0.2f, 0.2f), false);
    window.Draw(&health);
  }

  unsigned int experience;
  int health;
  DWORD damageTime;
};