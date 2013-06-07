#pragma once

#include "Sprite.hpp"

class PhysicsObject : public se::Sprite {
public:
  enum { G = 10 };
  enum State { STADING, INAIR, FALLING };
  PhysicsObject(int x = 0, int y = 0, int maxJump = 60) : se::Sprite(x, y), inAir(STADING), maxJump(maxJump) {}
protected:
  State inAir;
  int maxJump;
  int currentJump;
  void Tick();
};