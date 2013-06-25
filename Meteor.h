#pragma once

#include "Skill.h"

class Meteor : public Skill {
public:
  Meteor() : Skill(0, 0, 50, 100), speed(5) {
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
    destination = player.IsFlippedX() ? LEFT : RIGHT;
    if (!imageLoaded) LoadImage();
    SetX(player.GetX() + (destination == RIGHT ? 10 : -10));
    SetY(player.GetY() + 200);
    casting = true;
    isDrawing = true;
    FlipX(player.IsFlippedX());
  }

  bool imageLoaded;
  int speed;
  bool isDrawing;
};