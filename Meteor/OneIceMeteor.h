#pragma once

#include "BaseMeteor.h"

class OneIceMeteor : public Meteor {
public:
  std::shared_ptr<Meteor> base;
  OneIceMeteor() : base(new BaseMeteor()) {}

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    if (base->operation())
      return true;
    window.Draw(base.get());
    int left = base->GetX() - base->GetRange();
    int right = base->GetX() + base->GetWidth() + base->GetRange();
    for (auto it = enemies.begin(); it != enemies.end(); it++) {
      if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right) {
        it->Freeze(5000);
      }
    }
    return false;
  }
};