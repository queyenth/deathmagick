#pragma once

#include "Skill.h"

#include <iostream>

class Meteor : public Skill {
public:
  Meteor() : Skill() {

  }

  virtual ~Meteor() {

  }
private:
  void Render() const {
    MessageBox(NULL, L"Casting Meteor!", L"SKILL", MB_OK);
  }
};