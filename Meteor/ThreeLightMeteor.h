#pragma once

#include "BaseMeteor.h"

class ThreeLightMeteor : public Meteor {
  std::shared_ptr<BaseMeteor> meteors[20];
  bool waitingNew;
  int countOfMeteors;
  DWORD lastMeteor;
public:
  ThreeLightMeteor() : Meteor() {
    countOfMeteors = lastMeteor = 0;
  }

  virtual bool operation() override {
    if (GetTickCount() - lastMeteor > 250 && countOfMeteors < 20) {
      double angle = (70*3.14)/180;
      meteors[countOfMeteors] = std::shared_ptr<BaseMeteor>(new BaseMeteor());
      meteors[countOfMeteors]->Cast(player);
      meteors[countOfMeteors]->SetX(player.GetX() + rand()%600 - 300);
      meteors[countOfMeteors]->SetY(player.GetY() + 200);
      meteors[countOfMeteors]->speedX = 8 * cos(angle);
      meteors[countOfMeteors]->speedY = 8 * sin(angle);
      countOfMeteors++;
      lastMeteor = GetTickCount();
    }
    bool anyoneCasting = false;
    for (int i = 0; i < countOfMeteors; i++) {
      BaseMeteor *meteor = meteors[i].get();
      if (!meteor->casting) continue;
      meteor->operation();
      anyoneCasting = true; 
    }
    return anyoneCasting;
  }

};