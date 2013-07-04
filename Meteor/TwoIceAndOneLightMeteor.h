#pragma once

#include "TwoIceMeteor.h"
#include "OneLightMeteor.h"

class TwoIceAndOneLightMeteor : public Meteor {
public:
  std::shared_ptr<TwoIceMeteor> ice;
  std::shared_ptr<OneLightMeteor> light;

  TwoIceAndOneLightMeteor() : ice(new TwoIceMeteor()), light(new OneLightMeteor()) {}

  virtual void Cast(Player &player) override {
    ice->Cast(player);
  }

  // We need to optimize it
  virtual bool operation() override {
    // Если не рисуем ледяные шипы
    if (!ice->iceMaking) {
      // значит метеорит еще не упал, 
      if (ice->operation()) {
        // метеорит только что упал
        if (ice->iceMaking) {
          light->base = ice->base->base;
          // Оглушаем всех
          light->operation();
        }
      }
    }
    return ice->operation();
  }

};