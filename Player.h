#pragma once

#include "PhysicsObject.h"
#include "String.hpp"

class Player : public PhysicsObject {
public:
  Player(int x, int y, unsigned int exp) : PhysicsObject(x, y), experience(exp), health(100) {}
  Player() : PhysicsObject(0, 0), experience(0), health(100) {}
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
  }

  bool IsAlive() const {
    return health != 0;
  }

  int GetHealth() const {
    return health;
  }

private:
  unsigned int experience;
  int health;
};