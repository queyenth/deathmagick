#pragma once

#include "Entity.h"
#include "String.hpp"

class Player : public Entity {
public:
  Player(int x, int y, unsigned int exp) : Entity(x, y), experience(exp), health(100), damageTime(0) {}
  Player() : Entity(0, 0), experience(0), health(100), damageTime(0) {}
  virtual ~Player() {}
  void Jump() {
    if (inAir != STADING) return;
    inAir = INAIR;
    currentJump = maxJump;
  }

  virtual void Tick(std::vector<PhysicsObject *> things) override {
    damage.CheckEffect();
    freeze.CheckEffect();
    stun.CheckEffect();
    Entity::Tick(things);
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

  unsigned int experience;
  int health;
  DWORD damageTime;
};