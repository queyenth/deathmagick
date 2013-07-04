#pragma once

#include "TwoIceMeteor.h"
#include "OneFireMeteor.h"

class TwoIceAndOneFireMeteor : public Meteor {
public:
  std::shared_ptr<TwoIceMeteor> ice;
  std::shared_ptr<OneFireMeteor> fire;
  bool falled;
  bool iceFinished;

  TwoIceAndOneFireMeteor() : ice(new TwoIceMeteor()), fire(new OneFireMeteor()) {falled = false; iceFinished = true;}

  virtual void Cast(Player &player) override {
    ice->Cast(player);
  }

  // We need to optimize it
  virtual bool operation() override {
    if (!falled) {
      bool test = ice->operation();
      if (ice->iceMaking) {
        falled = true;
        fire->FireTime = true;
        fire->base = ice->base->base;
      }
      return test;
    }
    ice->base->base->Move(-fire->movedDistance, 0);
    if (iceFinished) {
      iceFinished = ice->operation();
    }
    fire->base->Move(fire->movedDistance, 0);
    return fire->operation() || iceFinished;
  }
};