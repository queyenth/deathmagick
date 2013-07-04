#pragma once

#include "OneFireMeteor.h"
#include "OneIceMeteor.h"

class OneFireAndOneIceMeteor : public Meteor {
public:
  std::shared_ptr<OneFireMeteor> fire;
  std::shared_ptr<OneIceMeteor> ice;
  
  OneFireAndOneIceMeteor() : fire(new OneFireMeteor()), ice(new OneIceMeteor()) {

  }

  virtual void Cast(Player &player) override {
    ice->Cast(player);
  }

  virtual bool operation() override {
    if (!fire->FireTime && !ice->operation()) {
      fire->FireTime = true;
      fire->base = ice->base;
    }
    else
      return fire->operation();
    return true;
  }

};