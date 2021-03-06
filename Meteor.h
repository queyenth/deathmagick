#pragma once

#include "Skill.h"
#include "Enemy.h"

#include <vector>
#include <algorithm>

class Meteor : public Skill {
public:
  Meteor() : Skill(0, 0, 50, 100) {
    imageLoaded = false;
    speed = 5;
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

  bool IsShoted(Enemy *enemy) {
    if (std::find(shoted.begin(), shoted.end(), enemy) != shoted.end())
      return true;
    return false;
  }

  bool imageLoaded;
  bool isDrawing;
  std::vector<Enemy *> shoted;
};