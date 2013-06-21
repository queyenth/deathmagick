#pragma once

#include "Entity.h"
#include "EntityEffect.h"
#include "String.hpp"

#include "Window.hpp"

class Enemy : public Entity {
public:
  Enemy(int x, int y, unsigned int exp)
    : Entity(x, y), experience(exp), health(100)
  {}
  Enemy() : Entity(0, 0), experience(0), health(100)
  {}
  virtual ~Enemy() {}
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
    this->damage.SetLong(2000);
    this->damage.MakeEffect();
    SetColor(this->damage.GetColor());
  }

  void Freeze(DWORD howLong) {
    freeze.SetLong(howLong);
    freeze.MakeEffect();
    SetColor(freeze.GetColor());
  }

  void Stun(DWORD howLong) {
    stun.SetLong(howLong);
    stun.MakeEffect();
    SetColor(stun.GetColor());
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
    if (!freeze.CheckEffect())
      SetColor(se::Color());
    damage.CheckEffect();
    Tick(floors);
  }

  unsigned int experience;
  int health;
  int moveSpeed;
  int attackSpeed;
};