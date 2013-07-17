#pragma once

#include "..\Meteor.h"
#include "..\GlobalObject.h"

#include <algorithm>

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
          if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right && !IsShoted(&*it)) {
            it->DamageHim(damage);
            shoted.push_back(&*it);
          }
        isDrawing = false;
        break;
      }
    }
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
    window.Draw(this);
    return isDrawing;
  }

  int speedX;
  int speedY;
};