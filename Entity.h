#pragma once

#include "PhysicsObject.h"
#include "EntityEffect.h"

#include <vector>

class Entity : public PhysicsObject {
public:
  enum { G = 2 };
  enum State { STADING, INAIR, FALLING, ONSTAIR };
  Entity(int x = 0, int y = 0, int maxJump = 30);
  virtual ~Entity() { }
  
  virtual void TryToMove(int offsetX, int offsetY, std::vector<PhysicsObject *> floors);
  virtual void Tick(std::vector<PhysicsObject *> things);

  bool CheckCollision(PhysicsObject *other) override;

  State inAir;
  Effect freeze;
  Effect damage;
  Effect stun;
  int speed;
protected:
  int maxJump;
  int currentJump;
};

