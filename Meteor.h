#pragma once

#include "Skill.h"

class Meteor : public Skill {
public:
  Meteor() : Skill(0, 0, 50, 100) {
    imageLoaded = false;
  }

  virtual ~Meteor() {

  }

  virtual void LoadImage() {
    image.LoadFromFile("img\\meteor.png");
    SetImage(image);
    imageLoaded = true;
  }

  virtual void Cast(Player &player) override {
    if (!imageLoaded) LoadImage();
    SetX(player.GetX() + (destination == RIGHT ? 10 : -10));
    SetY(player.GetY() + 200);
    casting = true;
    FlipX(player.IsFlippedX());
    destination = IsFlippedX() ? LEFT : RIGHT;
  }

  bool imageLoaded;
};