#include "PhysicsObject.h"

void PhysicsObject::Tick(int count, ...) {
  va_list vl;
  se::Renderable *value;
  switch (inAir) {
  case STADING:
    SetY(y - G);
    va_start(vl, count);
    for (int i = 0; i < count; i++) {
      value = va_arg(vl, se::Renderable *);
      if (!CheckCollision(*this, *value)) {
        inAir = FALLING;
        return ;
      }
    }
    SetY(y + G);
    break;
  case INAIR:
    if (currentJump <= 0)
      inAir = FALLING;
    else {
      currentJump -= G;
      SetY(y + currentJump);
    }
    break;
  case FALLING:
    currentJump += G;
    SetY(y - currentJump);
    va_start(vl, count);
    for (int i = 0; i < count; i++) {
      value = va_arg(vl, se::Renderable *);
      if (CheckCollision(*this, *value)) {
        SetY(value->GetY()+value->GetHeight());
        inAir = STADING;
        return ;
      }
    }
    va_end(vl);
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