#pragma once

#include "BaseMeteor.h"

class OneLightMeteor : public Meteor {
public:
  std::shared_ptr<Meteor> base;

  OneLightMeteor() : base(new BaseMeteor()) {
    LightTime = false;
    base->speed = 8;
  }

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    if (base->operation())
      return true;
    LightTime = true;
    window.Draw(base.get());
    int left = base->GetX() - base->GetRange();
    int right = base->GetX() + base->GetWidth() + base->GetRange();
    for (auto it = enemies.begin(); it != enemies.end(); it++)
      if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right)
        it->Stun(1000);
    return false;
  }

  bool LightTime;
};