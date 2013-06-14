#pragma once

#include "Skill.h"

#include <iostream>

class Meteor : public Skill {
public:
  Meteor() : Skill(0, 0, 50, 100) {

  }

  virtual ~Meteor() {

  }

  void Cast(Player &player) override {
    image.LoadFromFile("img\\meteor.png");
    SetImage(image);
    SetColor(se::Color(1.0f, 1.0f, 1.0f));
    SetX(player.GetX() + (destination == RIGHT ? 10 : -10));
    SetY(player.GetY() + 200);
    casting = true;
    FlipX(player.IsFlippedX());
    destination = IsFlippedX() ? LEFT : RIGHT;
  }

  void Tick(se::Window &window, int count, ...) override {
    va_list vl;
    se::Renderable *val;
    va_start(vl, count);
      for (int i = 0; i < count; i++) {
        val = va_arg(vl, se::Renderable *);
        if (PhysicsObject::CheckCollision(*this, *val)) {
          casting = false;
          return ;
        }
      }
    va_end(vl);
    window.Draw(this);
    switch (destination) {
    case LEFT:
      Move(-5, -5);
      break;
    case RIGHT:
      Move(5,-5);
      break;
    default:
      break;
    }
  }

};