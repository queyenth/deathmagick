#pragma once

#include "OneFireMeteor.h"
#include "OneIceMeteor.h"
#include "OneLightMeteor.h"

class OneFireAndOneIceAndOneLightMeteor : public Meteor {
public:
  std::shared_ptr<OneFireMeteor> fire;
  std::shared_ptr<OneIceMeteor> ice;
  std::shared_ptr<OneLightMeteor> light;
  
  OneFireAndOneIceAndOneLightMeteor() : fire(new OneFireMeteor()), ice(new OneIceMeteor()), light(new OneLightMeteor()) {}

  virtual void Cast(Player &player) override {
    light->Cast(player);
  }

  virtual bool operation() override {
    if (!fire->FireTime && !light->operation()) {
      ice->base = light->base;
      ice->operation();
      fire->base = ice->base;
      fire->FireTime = true;
    }
    else
      return fire->operation();
    return true;
  }

};