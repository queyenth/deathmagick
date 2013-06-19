#pragma once

#include "PhysicsObject.h"
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

  // We need make AI FUCKING AWESOME
  void AITick(std::vector<PhysicsObject *> floors) {
    static DWORD startTime = GetTickCount();
    static int dest = 1;
    if (GetTickCount() - startTime <= 2000) {
      TryToMove(dest*2, 0, floors);
    }
    else {
      dest = rand()%2;
      if (dest == 0) { dest = -1; this->FlipX(true); }
      else this->FlipX(false);
      startTime = GetTickCount();
    }
    Tick(floors);
  }

  unsigned int experience;
  int health;
  DWORD damageTime;
};