#include "Entity.h"

Entity::Entity(int x, int y, int maxJump) : PhysicsObject(x, y), inAir(STADING), maxJump(maxJump), currentJump(0) {}

void Entity::TryToMove(int offsetX, int offsetY, std::vector<PhysicsObject *> floors) {
  this->Move(offsetX, offsetY);
  bool canMove = true;
  for (auto i = floors.begin(); i != floors.end(); i++)
    if (CheckCollision(*i)) {
      canMove = false;
      break;
    }
  int lolka = x + offsetX;
  if (lolka <= 2)
    canMove = false;
  if (!canMove)
    this->Move(-offsetX, -offsetY);
}

void Entity::Tick(std::vector<PhysicsObject *> things) {
  bool floorUnderFoot = false;
  switch (inAir) {
  case STADING:
    SetY(y - G);
    for (auto i = things.begin(); i != things.end(); i++)
      if ((*i)->CheckCollision(this)) {
        floorUnderFoot = true;
        break;
      }
    SetY(y + G);
    if (!floorUnderFoot) {
      inAir = FALLING;
      currentJump = 0;
    }
    break;
  case INAIR:
    if (currentJump <= 0)
      inAir = FALLING;
    else {
      currentJump -= G;
      SetY(y + currentJump);
      for (auto i = things.begin(); i != things.end(); i++)
        if ((*i)->CheckCollision(this))
          inAir = FALLING;
      break;
    }
    break;
  case FALLING:
    currentJump += G;
    SetY(y - currentJump);
    for (auto i = things.begin(); i != things.end(); i++)
      if ((*i)->CheckCollision(this)) {
        inAir = STADING;
      }
    break;
  case ONSTAIR:
    break;
  }
}

bool Entity::CheckCollision(PhysicsObject *other) {
  unsigned int width = GetX() + GetWidth();
	unsigned int height = GetY() + GetHeight();
	unsigned int aWidth = other->GetX() + other->GetWidth();
	unsigned int aHeight = other->GetY() + other->GetHeight();

	return (GetX() < aWidth && GetY() < aHeight && other->GetX() < width && other->GetY() < height);
}