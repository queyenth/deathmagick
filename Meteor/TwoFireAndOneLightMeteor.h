#pragma once

#include "TwoFireMeteor.h"
#include "OneLightMeteor.h"

class TwoFireAndOneLightMeteor : public Meteor {
  std::shared_ptr<TwoFireMeteor> fire;
  std::shared_ptr<OneLightMeteor> light;
public:
  TwoFireAndOneLightMeteor() : fire(new TwoFireMeteor()), light(new OneLightMeteor()) {
  }

  virtual void Cast(Player &player) override {
    fire->Cast(player);
    fire->base->base->speed = light->base->speed;
  }

  virtual bool operation() override {
    if (!fire->base->FireTime) {
      fire->operation();
      if (fire->base->FireTime) {
        light->base = fire->base->base;
        light->operation();
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