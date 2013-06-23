#include "Entity.h"

Entity::Entity(int x, int y, int maxJump) : PhysicsObject(x, y), inAir(STADING), maxJump(maxJump), currentJump(0), speed(3),
  damage(se::Color(1.0f, 0.4f, 0.4f, 1.0f)),
  stun(se::Color(0.6f, 0.6f, 0.6f, 1.0f)), freeze(se::Color(0.4f, 0.4f, 1.0f, 0.5f)) {}

void Entity::TryToMove(int offsetX, int offsetY, std::vector<PhysicsObject *> floors) {
  if (!stun.UnderEffect()) {
    int speedX = !freeze.UnderEffect() ? speed*offsetX : speed*offsetX/2;
    int speedY = !freeze.UnderEffect() ? speed*offsetY : speed*offsetY/2;
    this->Move(speedX, speedY);
    bool canMove = true;
    for (auto i = floors.begin(); i != floors.end(); i++)
      if (CheckCollision(*i)) {
        canMove = false;
        break;
      }
    int lolka = x + speedX;
    if (lolka <= 2)
      canMove = false;
    if (!canMove)
      this->Move(-speedX, -speedY);
  }
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
        this->SetY((*i)->GetY()+(*i)->GetHeight());
        inAir = STADING;
        break;
      }
    break;
  case ONSTAIR:
    break;
  }
}

bool Entity::CheckCollision(PhysicsObject *other) {
  int width = GetX() + GetWidth();
	int height = GetY() + GetHeight();
	int aWidth = other->GetX() + other->GetWidth();
	int aHeight = other->GetY() + other->GetHeight();

	return (GetX() < aWidth && GetY() < aHeight && other->GetX() < width && other->GetY() < height);
}