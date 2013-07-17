#pragma once

#include "BaseMeteor.h"

class OneFireMeteor : public Meteor {
public:
  std::shared_ptr<Meteor> base;
  
  OneFireMeteor() : base(new BaseMeteor()) {
    movedDistance = 0; FireTime = false;
    damage.damage = 25;
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
      if (it->CheckCollision(base.get()) && !IsShoted(&*it)) {
        it->DamageHim(damage);
        shoted.push_back(&*it);
      }
    window.Draw(base.get());
    return true;
  }

  int movedDistance;
  bool FireTime;
};