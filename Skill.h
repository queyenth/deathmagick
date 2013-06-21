#pragma once

#include "Player.h"

class Skill : public Entity {
public:
  enum Destination { UP, DOWN, RIGHT, LEFT };

  Skill() : Entity(0, 0), damage(0), range(0), casting(false) {}
  Skill(int x, int y, int damage, int range) : Entity(x, y), damage(damage), range(range), casting(false) { }
  virtual ~Skill() {}

  virtual void Cast(Player &) = 0;
  virtual bool operation() = 0;
  
  virtual int GetDamage() {
    return damage;
  }
  
  virtual int GetRange() {
    return range;
  }

  bool casting;
  int damage;
  int range;
  Destination destination;
};