#pragma once

#include "PhysicsObject.h"
#include "EntityEffect.h"
#include "Window.hpp"
#include "Damage.h"

#include <vector>

class Entity : public PhysicsObject {
public:
  enum { G = 2 };
  enum State { STADING, INAIR, FALLING, ONSTAIR };
  Entity(int x = 0, int y = 0, int health = 100, int experience = 0, int speed = 3, int maxJump = 30);
  virtual ~Entity() { }
  
  virtual void TryToMove(int offsetX, int offsetY, std::vector<PhysicsObject *> floors);
  virtual void Tick(std::vector<PhysicsObject *> things);
  virtual void DrawHealth(se::Window &window) const {};

  void Jump();
  void DamageHim(Damage damage);
  void Freeze(DWORD howLong);
  void Stun(DWORD howLong);
  bool IsAlive() const;
  int GetHealth() const;
  void SetHealth(int health);

  bool CheckCollision(PhysicsObject *other) override;

  State inAir;
  Effect freeze;
  Effect damage;
  Effect stun;
  int speed;
  int experience;
  bool immunity[Damage::ALL];
  vector<Damage> damages;
protected:
  int maxJump;
  int currentJump;
  int health;
};

