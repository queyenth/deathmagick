#pragma once

#include "Player.h"

class Skill : public se::Sprite {
public:
  Skill() : se::Sprite(0, 0), damage(0), range(0), impr(0, 0, 0), casting(false) {}
  Skill(int x, int y, int damage, int range) : se::Sprite(x, y), impr(0, 0, 0), damage(0), range(0), casting(false) { }
  virtual ~Skill() {}

  virtual void Cast(Player &) = 0;
  virtual void Tick(se::Window &) = 0;
  
  bool casting;
protected:
  int damage;
  int range;

  struct tagIMPR {
    int k1;
    int k2;
    int k3;
    tagIMPR(int k1, int k2, int k3) : k1(k1), k2(k2), k3(k3) {}
  } impr;
};