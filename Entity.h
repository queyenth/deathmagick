#pragma once

#include "PhysicsObject.h"

#include <vector>

class Entity : public PhysicsObject {
public:
  enum { G = 2 };
  enum State { STADING, INAIR, FALLING, ONSTAIR };
  Entity(int x = 0, int y = 0, int maxJump = 30);
  virtual ~Entity() { }
  
  void TryToMove(int offsetX, int offsetY, std::vector<PhysicsObject *> floors);
  void Tick(std::vector<PhysicsObject *> things);

  bool CheckCollision(PhysicsObject *other) override;

  State inAir;
protected:
  int maxJump;
  int currentJump;
};