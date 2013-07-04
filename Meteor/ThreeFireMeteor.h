#pragma once

#include "TwoFireMeteor.h"

class ThreeFireMeteor : public Meteor {
public:
  std::shared_ptr<TwoFireMeteor> fire;

  ThreeFireMeteor() : fire (new TwoFireMeteor()) {
    waveTime = false;
    waveTimes = 0;
    waveImage.LoadFromFile("img\\sphere.png");
    waveSprite.SetImage(waveImage);
    waveSprite.SetColor(se::Color(1.0f, 1.0f, 1.0f, 0.7f));
  }

  virtual void Cast(Player &player) override {
    fire->Cast(player);
  }

  virtual bool operation() override {
    if (waveTime) {
      if (waveTimes == 25) {
        waveTimes = 0;
        int left = waveSprite.GetX();
        int right = waveSprite.GetX()+waveSprite.GetWidth();
        for (auto it = enemies.begin(); it != enemies.end(); it++)
          if (left <= it->GetX() && it->GetX()+it->GetWidth() <= right)
            it->DamageHim(200);
        return false;
      }
      waveSprite.SetWidth(50+waveTimes*8);
      waveSprite.SetHeight(20+waveTimes*8);
      waveSprite.SetX(fire->base->base->GetX()-waveSprite.GetWidth()/2);
      waveTimes++;
      window.Draw(&waveSprite);
      return true;
    }
    if (!fire->operation()) {
      waveTime = true;
      waveSprite.SetY(fire->base->base->GetY());
    }
  }

  bool waveTime;
  se::Image waveImage;
  se::Sprite waveSprite;
  int waveTimes;

};