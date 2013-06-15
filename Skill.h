#pragma once

#include "Player.h"

struct tagIMPR {
    int k1;
    int k2;
    int k3;
    tagIMPR(int k1, int k2, int k3) : k1(k1), k2(k2), k3(k3) {}
 };

class Skill : public PhysicsObject {
public:
  enum Destination { UP, DOWN, RIGHT, LEFT };

  Skill() : PhysicsObject(0, 0), damage(0), range(0), impr(0, 0, 0), casting(false) {}
  Skill(int x, int y, int damage, int range) : PhysicsObject(x, y), impr(0, 0, 0), damage(damage), range(range), casting(false) { }
  virtual ~Skill() {}

  virtual void Cast(Player &) = 0;
  virtual void Tick(se::Window &, int count, ...) = 0;
  
  virtual int GetDamage() {
    return damage;
  }
  
  virtual int GetRange() {
    return range;
  }

  bool casting;
protected:
  int damage;
  int range;
  Destination destination;
  tagIMPR impr;
};