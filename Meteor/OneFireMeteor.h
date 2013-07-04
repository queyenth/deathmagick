#pragma once

#include "BaseMeteor.h"

class OneFireMeteor : public Meteor {
public:
  std::shared_ptr<Meteor> base;
  
  OneFireMeteor() : base(new BaseMeteor()) {
    movedDistance = 0; FireTime = false;
  }
  
  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    if (!FireTime) {
      if (base->operation())
        return true;
      FireTime = true;
    }
    if (movedDistance > 300) {
      movedDistance = 0;
      return false;
    }
    window.Draw(base.get());
    if (base->destination == LEFT) {
      base->Rotate(8);
      base->Move(-base->speed, 0);
    }
    else {
      base->Rotate(-8);
      base->Move(base->speed, 0);
    }
    movedDistance += base->speed;
    for (auto it = enemies.begin(); it != enemies.end(); it++)
      if (it->CheckCollision(base.get()))
        it->DamageHim(GetDamage());
    return true;
  }

  int movedDistance;
  bool FireTime;
};