#pragma once

#include "OneFireMeteor.h"
#include "OneLightMeteor.h"

// FIXME: Wtf
class OneFireAndOneLightMeteor : public Meteor {
public:
  //std::shared_ptr<Meteor> base;
  std::shared_ptr<OneFireMeteor> fire;
  std::shared_ptr<OneLightMeteor> light;
  
  OneFireAndOneLightMeteor() : fire(new OneFireMeteor()), light(new OneLightMeteor()) {

  }

  virtual void Cast(Player &player) override {
    light->Cast(player);
  }

  virtual bool operation() override {
    if (!fire->FireTime && !light->operation()) {
      fire->FireTime = true;
      fire->base = light->base;
    }
    else
      return fire->operation();
    return true;
  }

};