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
    light->Cast(player);
    fire->base->base->speed = light->base->speed;
  }

  virtual bool operation() override {
    // making light, then it fall, it return 
    if (!fire->base->FireTime) {
      if (!light->operation()) {
        fire->base->FireTime = true;
        fire->base->base = light->base;
      }
      return true;
    }
    else
      return fire->operation();
  }

  se::Image fireImage;
  Entity fireSprite;
  int lastFire;
};