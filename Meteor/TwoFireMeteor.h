#pragma once

#include "OneFireMeteor.h"

class TwoFireMeteor : public Meteor {
public:
  std::shared_ptr<OneFireMeteor> base;
  
  TwoFireMeteor() : base(new OneFireMeteor()) {
    lastFire = 0;
  }

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    bool returnBase = base->operation();
    Meteor *meteor = base->base.get();
    if (base->FireTime) {
      if (!fireImage.IsValid()) {
        fireImage.LoadFromFile("img\\fire.png");
        fireSprite.SetImage(fireImage);
        fireSprite.SetY(meteor->GetY());
        lastFire = meteor->GetX();
      }
      if (meteor->GetX() - lastFire > fireSprite.GetWidth() && !meteor->IsFlippedX()) {
        lastFire = meteor->GetX();
        fireSprite.SetX(lastFire);
        effects.push_back(DrawSomeTime<Entity>(std::shared_ptr<Entity>(new Entity(fireSprite)), 3000));
      }
      else if (lastFire - meteor->GetX() > fireSprite.GetWidth() && meteor->IsFlippedX()) {
        lastFire = meteor->GetX();
        fireSprite.SetX(lastFire);
        effects.push_back(DrawSomeTime<Entity>(std::shared_ptr<Entity>(new Entity(fireSprite)), 3000));
      }
    }
    return returnBase;
  }

  se::Image fireImage;
  Entity fireSprite;
  int lastFire;
};