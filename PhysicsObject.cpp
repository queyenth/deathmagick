#include "PhysicsObject.h"

void PhysicsObject::Tick() {
  switch (inAir) {
  case STADING:
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
    if (y <= 0) {
      inAir = STADING;
      SetY(0);
    }
    else {
      currentJump += G;
      SetY(y - currentJump);
    }
    break;
  }
}