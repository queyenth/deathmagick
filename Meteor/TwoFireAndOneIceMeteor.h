#pragma once

#include "TwoFireMeteor.h"
#include "OneIceMeteor.h"

class TwoFireAndOneIceMeteor : public Meteor {
  std::shared_ptr<TwoFireMeteor> fire;
  std::shared_ptr<OneIceMeteor> ice;
public:
  TwoFireAndOneIceMeteor() : fire(new TwoFireMeteor()), ice(new OneIceMeteor()) {
  }

  virtual void Cast(Player &player) override {
    fire->Cast(player);
  }

  virtual bool operation() override {
    if (!fire->base->FireTime) {
      fire->operation();
      if (fire->base->FireTime) {
        ice->base = fire->base->base;
        ice->operation();
      }
      return true;
    }
    else {
      return fire->operation();
    }
  }

  se::Image fireImage;
  Entity fireSprite;
  int lastFire;
};