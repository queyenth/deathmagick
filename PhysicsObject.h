#pragma once

#include "Sprite.hpp"

class PhysicsObject : public se::Sprite {
public:
  PhysicsObject(int x = 0, int y = 0);
  virtual ~PhysicsObject() {}
  
  virtual bool CheckCollision(PhysicsObject *other) const = 0;
};