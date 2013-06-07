#pragma once

#include "PhysicsObject.h"
#include "String.hpp"

class Player : public PhysicsObject {
public:
  Player(int x, int y, unsigned int exp) : PhysicsObject(x, y), experience(exp) {}
  virtual ~Player() {}
private:
  unsigned int experience;
};