#pragma once

#include "Sprite.hpp"

#include <vector>

namespace se {
  class Line;
}

class PhysicsObject : public se::Sprite {
public:
  PhysicsObject(int x = 0, int y = 0);
  virtual ~PhysicsObject() {}
  
  virtual bool CheckCollision(PhysicsObject *other) = 0;
};