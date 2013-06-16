#pragma once

#include "Sprite.hpp"

#include <vector>

class PhysicsObject : public se::Sprite {
public:
  enum { G = 2 };
  enum State { STADING, INAIR, FALLING, ONSTAIR };
  PhysicsObject(int x = 0, int y = 0, int maxJump = 30);
  void Tick(std::vector<se::Sprite> &things);
  void TryToMove(unsigned int offsetX, unsigned int offsetY, std::vector<se::Sprite> &floors);

  static bool CheckCollision(const se::Renderable &first, const se::Renderable &second);
  
  State inAir;
protected:
  int maxJump;
  int currentJump;
};