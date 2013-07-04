#pragma once

#include "OneIceMeteor.h"
#include "OneLightMeteor.h"

class OneIceAndOneLightMeteor : public Meteor {
public:
  std::shared_ptr<OneLightMeteor> light;
  std::shared_ptr<OneIceMeteor> ice;
  
  OneIceAndOneLightMeteor() : light(new OneLightMeteor()), ice(new OneIceMeteor()) {

  }

  virtual void Cast(Player &player) override {
    ice->Cast(player);
  }

  virtual bool operation() override {
    if (!ice->operation()) {
      light->base = ice->base;
      return light->operation();
    }
    return true;
  }

};