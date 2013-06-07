#include "PhysicsObject.h"

void PhysicsObject::Tick() {
  static int yC;
  switch (inAir) {
  case STADING:
    break;
  case INAIR:
    if (currentJump <= 0)
      inAir = FALLING;
    else {
      yC = y;
      currentJump = maxJump;
      currentJump -= G;
      y += currentJump;
    }
    break;
  case FALLING:
    if (y >= yC) {
      currentJump += G;
      y -= currentJump;
    }
    else
      inAir = STADING;
  }
}