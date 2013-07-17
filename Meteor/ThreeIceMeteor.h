#pragma once

#include "BaseMeteor.h"

class ThreeIceMeteor : public Meteor {
  std::shared_ptr<Meteor> base;
public:
  ThreeIceMeteor() : base(new BaseMeteor()) {
    sphereTime = false;
    damage = Damage(Damage::ICE, 25);
  }

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    if (sphereTime) {
      if (!iceSphereImage.IsValid()) {
        iceSphereImage.LoadFromFile("img\\ice_sphere.png");
        iceSphereSprite.SetImage(iceSphereImage);
        iceSphereSprite.SetX(base->GetX()-150);
        iceSphereSprite.SetY(base->GetY());
        iceSphereSprite.SetWidth(300);
        iceSphereSprite.SetHeight(150);
        iceSphereSprite.SetColor(se::Color(1.0f, 1.0f, 1.0f, 0.5f));
        fallingTime = secondRemaining =  GetTickCount();
      }
      if (secondRemaining - fallingTime > 5000)
        return false;
      else {
        window.Draw(&iceSphereSprite);
        if (GetTickCount() - secondRemaining > 1000) {
          secondRemaining = GetTickCount();
          for (auto i = enemies.begin(); i != enemies.end(); i++) {
            if (i->CheckCollision(&iceSphereSprite)) {
              i->DamageHim(damage);
              i->Freeze(5000);
            }
          }
        }
      }
    }
    if (!base->operation()) {
      sphereTime = true;
      int left = base->GetX() - base->GetRange();
      int right = base->GetX() + base->GetWidth() + base->GetRange();
      for (auto i = enemies.begin(); i != enemies.end(); i++)
        if (left <= i->GetX() && i->GetX()+i->GetWidth() <= right)
          i->Freeze(5000);
    }
    return true;
  }

  se::Image iceSphereImage;
  Entity iceSphereSprite;
  DWORD fallingTime;
  DWORD secondRemaining;
  bool sphereTime;
};