#pragma once

#include "..\Meteor.h"
#include "..\GlobalObject.h"

class BaseMeteor : public Meteor {
public:
  BaseMeteor() : Meteor() {speedX = speedY = speed;}
  virtual bool operation() override {
    if (!isDrawing) return false;
    for (auto i = floors.begin(); i != floors.end(); i++) {
      if ((*i)->CheckCollision(this)) {
        int left = GetX() - GetRange();
        int right = GetX() + GetWidth() + GetRange();
        for (auto it = enemies.begin(); it != enemies.end(); it++)
          if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right)
            it->DamageHim(GetDamage());
        isDrawing = false;
        break;
      }
    }
    window.Draw(this);
    switch (destination) {
    case LEFT:
      Move(-speedX, -speedY);
      break;
    case RIGHT:
      Move(speedX, -speedY);
      break;
    default:
      break;
    }
    return isDrawing;
  }

  int speedX;
  int speedY;
};