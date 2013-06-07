#pragma once

#include "Skill.h"

#include <iostream>

class Meteor : public Skill {
public:
  Meteor() : Skill() {
    se::Image image;
    image.LoadFromFile("img\\meteor.png");
    SetImage(image);
  }

  virtual ~Meteor() {

  }

  void Cast(Player &player) {
    SetX(player.GetX()+10);
    SetY(player.GetY()+60);
    casting = true;
  }

  void Tick(se::Window &window) {
    if (y <= 0) {
      SetY(0);
      casting = false;
    }
    else
      Move(5, -5);
  }

};