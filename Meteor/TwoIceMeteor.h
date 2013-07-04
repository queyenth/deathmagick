#pragma once

#include "OneIceMeteor.h"

class TwoIceMeteor : public Meteor {
public:
  std::shared_ptr<OneIceMeteor> base;

  TwoIceMeteor() : base(new OneIceMeteor()) {
    range = 200;
    countOfFrames = 0;
    iceMaking = false;
    damage = 25;
  }

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    if (!iceMaking) {
      if (!base->operation())
        iceMaking = true;
    }
    else {
      Meteor *meteor = base->base.get();
      if (!iceFromLandImage.IsValid()) {
        iceFromLandImage.LoadFromFile("img\\ice_from_lang.png");
        iceFromLand.SetImage(iceFromLandImage);
        iceFromLand.SetY(meteor->GetY() - iceFromLandImage.GetWidth());
      }
      iceFromLand.Move(0, 1);
      int left = meteor->GetX() - GetRange();
      int right = meteor->GetX() + meteor->GetWidth() + GetRange();
      if (countOfFrames == 21) {
        for (auto it = enemies.begin(); it != enemies.end(); it++)
          if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right)
            it->DamageHim(GetDamage());
        return false;
      }
      for (int i = left; i < right; i+=iceFromLandImage.GetWidth()) {
        iceFromLand.SetX(i);
        window.Draw(&iceFromLand);
      }
      countOfFrames++;
    }
    return true;
  }

  se::Sprite iceFromLand;
  se::Image iceFromLandImage;
  int countOfFrames;
  bool iceMaking;
};