#pragma once

#include "OneLightMeteor.h"

class TwoLightMeteor : public Meteor {
public:
  std::shared_ptr<OneLightMeteor> base;
  
  TwoLightMeteor() : base(new OneLightMeteor()) {
    countOfMeteors = 0;
    waitingNew = false;
  }

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    if (waitingNew && GetTickCount() - lastMeteor > 500) {
      base->Cast(player);
      countOfMeteors++;
      waitingNew = false;
    }
    if (countOfMeteors != 3) {
      if (!base->operation())
        waitingNew = true;
    }
    else
      return false;
    return true;
  }

  int countOfMeteors;
  DWORD lastMeteor;
  bool waitingNew;
};