#pragma once

#include "OneIceMeteor.h"
#include "TwoLightMeteor.h"

class TwoLightAndOneIceMeteor : public Meteor {
public:
  std::shared_ptr<TwoLightMeteor> light;
  std::shared_ptr<OneIceMeteor> ice;
  
  TwoLightAndOneIceMeteor() : light(new TwoLightMeteor()), ice(new OneIceMeteor()) {
    countOfMeteors = 0;
  }

  virtual void Cast(Player &player) override {
    light->Cast(player);
  }

  virtual bool operation() override {
    bool retVal = light->operation();
    if (light->waitingNew) {
      ice->base = light->base->base;
      ice->operation();
    }
    return retVal;
  }

  int countOfMeteors;
};