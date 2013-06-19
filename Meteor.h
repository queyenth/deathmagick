#pragma once

#include "Skill.h"

#include <iostream>

class Meteor : public Skill {
public:
  Meteor() : Skill(0, 0, 50, 100) {
    imageLoaded = false;
  }

  virtual ~Meteor() {

  }

  void LoadImage() {
    image.LoadFromFile("img\\meteor.png");
    SetImage(image);
    imageLoaded = true;
  }

  void Cast(Player &player) override {
    if (!imageLoaded) LoadImage();
    SetX(player.GetX() + (destination == RIGHT ? 10 : -10));
    SetY(player.GetY() + 200);
    casting = true;
    FlipX(player.IsFlippedX());
    destination = IsFlippedX() ? LEFT : RIGHT;
  }

  void Tick(se::Window &window, std::vector<PhysicsObject *> things) override {
    for (auto i = things.begin(); i != things.end(); i++) {
      if ((*i)->CheckCollision(this)) {
        casting = false;
        return ;
      }
    }
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

  bool imageLoaded;

};