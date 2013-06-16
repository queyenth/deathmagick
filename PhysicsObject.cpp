#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(int x, int y, int maxJump) : se::Sprite(x, y), inAir(STADING), maxJump(maxJump), currentJump(0) {}

void PhysicsObject::TryToMove(unsigned int offsetX, unsigned int offsetY, std::vector<se::Sprite> &floors) {
  this->Move(offsetX, offsetY);
  bool canMove = true;
  for (auto i = floors.begin(); i != floors.end(); i++)
    if (CheckCollision(*this, *i)) {
      canMove = false;
      break;
    }
  if (!canMove)
    this->Move(-offsetX, -offsetY);
}

void PhysicsObject::Tick(std::vector<se::Sprite> &things) {
  bool floorUnderFoot = false;
  switch (inAir) {
  case STADING:
    SetY(y - G);
    for (auto i = things.begin(); i != things.end(); i++)
      if (CheckCollision(*this, *i)) {
        floorUnderFoot = true;
        break;
      }
    SetY(y + G);
    if (!floorUnderFoot)
      inAir = FALLING;
    break;
  case INAIR:
    if (currentJump <= 0)
      inAir = FALLING;
    else {
      currentJump -= G;
      SetY(y + currentJump);
      for (auto i = things.begin(); i != things.end(); i++)
        if (CheckCollision(*this, *i))
          inAir = FALLING;
      break;
    }
    break;
  case FALLING:
    currentJump += G;
    SetY(y - currentJump);
    for (auto i = things.begin(); i != things.end(); i++)
      if (CheckCollision(*this, *i)) {
        SetY(i->GetY()+i->GetHeight());
        inAir = STADING;
      }
    break;
  case ONSTAIR:
    break;
  }
}

bool PhysicsObject::CheckCollision(const se::Renderable &first, const se::Renderable &second) {
  unsigned int width = first.GetX() + first.GetWidth();
	unsigned int height = first.GetY() + first.GetHeight();
	unsigned int aWidth = second.GetX() + second.GetWidth();
	unsigned int aHeight = second.GetY() + second.GetHeight();

	return (first.GetX() < aWidth && first.GetY() < aHeight && second.GetX() < width && second.GetY() < height);
}