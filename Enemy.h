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

  void DamageHim(int damageSize) {
    if (damage.UnderEffect()) return ;
	  if (health - damageSize <= 0)
      health = 0;
	  else
	    health -= damageSize;
    char text[5];
    sprintf_s(text, 5, "%d", damageSize);
    damageString.push_back(DrawSomeTime<se::String>(std::shared_ptr<se::String>(new se::String(text, font, x+GetWidth(), y+GetHeight(), se::Color(1.0f, 1.0f, 1.0f), false)), 1000));
    damage.SetLong(500);
    damage.MakeEffect();
    SetColor(damage.GetColor());
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