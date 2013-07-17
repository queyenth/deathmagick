#pragma once

#include "Player.h"

class Skill : public Entity {
public:
  enum Destination { UP, DOWN, RIGHT, LEFT };

  Skill() : Entity(0, 0), damage(Damage::PHYSICAL, 0), range(0), casting(false) {}
  Skill(int x, int y, int damage, int range) : Entity(x, y), damage(Damage::PHYSICAL, damage), range(range), casting(false) { }
  virtual ~Skill() {}

  virtual void Cast(Player &) = 0;
  virtual bool operation() = 0;
  
  virtual Damage GetDamage() {
    return damage;
  }
  
  virtual int GetRange() {
    return range;
  }

  Damage damage;
  int range;
  bool casting;
  Destination destination;
};