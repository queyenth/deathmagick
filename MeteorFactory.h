#pragma once

#include "Meteor.h"

class BaseMeteor : public Meteor {
public:
  BaseMeteor() : Meteor() {}
  virtual bool operation() override {
    if (!isDrawing) return false;
    for (auto i = floors.begin(); i != floors.end(); i++) {
      if ((*i)->CheckCollision(this)) {
        int left = GetX() - GetRange();
        int right = GetX() + GetWidth() + GetRange();
        for (auto it = enemies.begin(); it != enemies.end(); it++) {
          if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right) {
            wchar_t text[5];
            wsprintf(text, L"%d", GetDamage());
            damageString.push_back(DrawSomeTime(std::make_shared<se::String>(se::String(text, font, it->GetX()+it->GetWidth()+2, it->GetY()+it->GetHeight(), se::Color(1.0f, 1.0f, 1.0f), false)), 1000));
            it->DamageHim(GetDamage());
          }
        }
        isDrawing = false;
        break;
      }
    }
    window.Draw(this);
    switch (destination) {
    case LEFT:
      Move(-speed, -speed);
      break;
    case RIGHT:
      Move(speed, -speed);
      break;
    default:
      break;
    }
    return isDrawing;
  }
};

class OneFireMeteor : public Meteor {
  std::shared_ptr<Meteor> base;
public:
  OneFireMeteor() : Meteor() {movedDistance = 0; FireTime = false;}
  OneFireMeteor(Meteor *meteor) : Meteor(), base(meteor) { movedDistance = 0; FireTime = false; }
  
  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    if (!FireTime) {
      if (base->operation())
        return true;
      FireTime = true;
    }
    if (movedDistance > 300) {
      movedDistance = 0;
      return false;
    }
    window.Draw(base.get());
    if (base->destination == LEFT)
      base->Move(-base->speed, 0);
    else
      base->Move(base->speed, 0);
    movedDistance += base->speed;
    for (auto it = enemies.begin(); it != enemies.end(); it++) {
      if (it->CheckCollision(base.get()) && !it->damage.UnderEffect()) {
        wchar_t text[5];
        wsprintf(text, L"%d", GetDamage());
        damageString.push_back(DrawSomeTime(std::make_shared<se::String>(se::String(text, font, it->GetX()+it->GetWidth()+2, it->GetY()+it->GetHeight(), se::Color(1.0f, 1.0f, 1.0f), false)), 1000));
        it->DamageHim(GetDamage());
      }
    }
    return true;
  }

  int movedDistance;
  bool FireTime;
};

class OneIceMeteor : public Meteor {
  std::shared_ptr<Meteor> base;
public:
  OneIceMeteor() : Meteor() {}
  OneIceMeteor(Meteor *meteor) : Meteor(), base(meteor) {}

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    if (base->operation())
      return true;
    window.Draw(base.get());
    int left = GetX() - GetRange();
    int right = base->GetX() + base->GetWidth() + base->GetRange();
    for (auto it = enemies.begin(); it != enemies.end(); it++) {
      if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right) {
        it->Freeze(2000);
      }
    }
    return false;
  }
};

class OneFireAndOneIceMeteor : public Meteor {
  std::shared_ptr<Meteor> base;
public:
  OneFireAndOneIceMeteor(Meteor *meteor) : base(meteor) {FireTime = false; movedDistance = 0;}

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    if (!FireTime) {
      if (base->operation())
        return true;
      Ice();
      FireTime = true;
    }
    return Fire();
  }

  bool Ice() {
    window.Draw(base.get());
    int left = GetX() - GetRange();
    int right = base->GetX() + base->GetWidth() + base->GetRange();
    for (auto it = enemies.begin(); it != enemies.end(); it++)
      if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right)
        it->Freeze(2000);
    return false;
  }

  bool Fire() {
    if (movedDistance > 300) {
      movedDistance = 0;
      return false;
    }
    window.Draw(base.get());
    if (base->destination == LEFT)
      base->Move(-base->speed, 0);
    else
      base->Move(base->speed, 0);
    movedDistance += base->speed;
    for (auto it = enemies.begin(); it != enemies.end(); it++) {
      if (it->CheckCollision(base.get()) && !it->damage.UnderEffect()) {
        wchar_t text[5];
        wsprintf(text, L"%d", GetDamage());
        damageString.push_back(DrawSomeTime(std::make_shared<se::String>(se::String(text, font, it->GetX()+it->GetWidth()+2, it->GetY()+it->GetHeight(), se::Color(1.0f, 1.0f, 1.0f), false)), 1000));
        it->DamageHim(GetDamage());
      }
    }
    return true;
  }

  bool FireTime;
  int movedDistance;
};

class OneLightMeteor : public Meteor {
  std::shared_ptr<Meteor> base;
public:
  OneLightMeteor(Meteor *meteor) : base(meteor) {}

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    base->speed = 8;
    if (base->operation())
      return true;
    window.Draw(base.get());
    int left = GetX() - GetRange();
    int right = base->GetX() + base->GetWidth() + base->GetRange();
    for (auto it = enemies.begin(); it != enemies.end(); it++)
      if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right)
        it->Stun(1000);
    return false;
  }

};

class OneFireAndOneLightMeteor : public Meteor {
  std::shared_ptr<Meteor> base;
public:
  OneFireAndOneLightMeteor(Meteor *meteor) : base(meteor) {FireTime = false; movedDistance = 0;}

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    base->speed = 8;
    if (!FireTime) {
      if (base->operation())
        return true;
      Light();
      FireTime = true;
    }
    return Fire();
  }

  bool Light() {
    window.Draw(base.get());
    int left = GetX() - GetRange();
    int right = base->GetX() + base->GetWidth() + base->GetRange();
    for (auto it = enemies.begin(); it != enemies.end(); it++)
      if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right)
        it->Stun(2000);
    return false;
  }

  bool Fire() {
    if (movedDistance > 300) {
      movedDistance = 0;
      return false;
    }
    window.Draw(base.get());
    if (base->destination == LEFT)
      base->Move(-base->speed, 0);
    else
      base->Move(base->speed, 0);
    movedDistance += base->speed;
    for (auto it = enemies.begin(); it != enemies.end(); it++) {
      if (it->CheckCollision(base.get()) && !it->damage.UnderEffect()) {
        wchar_t text[5];
        wsprintf(text, L"%d", GetDamage());
        damageString.push_back(DrawSomeTime(std::make_shared<se::String>(se::String(text, font, it->GetX()+it->GetWidth()+2, it->GetY()+it->GetHeight(), se::Color(1.0f, 1.0f, 1.0f), false)), 1000));
        it->DamageHim(GetDamage());
      }
    }
    return true;
  }

  bool FireTime;
  int movedDistance;
};

class OneIceAndOneLightMeteor : public Meteor {
  std::shared_ptr<Meteor> base;
public:
  OneIceAndOneLightMeteor(Meteor *meteor) : base(meteor) {}

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    if (base->operation())
      return true;
    window.Draw(base.get());
    int left = base->GetX() - base->GetRange();
    int right = base->GetX() + base->GetWidth() + base->GetRange();
    for (auto it = enemies.begin(); it != enemies.end(); it++)
      if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right) {
        it->Freeze(2000);
        it->Stun(2000);
      }
    return false;
  }
};

class OneFireAndOneIceAndOneLightMeteor : public Meteor {
  std::shared_ptr<Meteor> base;
public:
  OneFireAndOneIceAndOneLightMeteor(Meteor *meteor) : base(meteor) {FireTime = false; movedDistance = 0;}

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    if (!FireTime) {
      if (base->operation())
        return true;
      window.Draw(base.get());
      int left = base->GetX() - base->GetRange();
      int right = base->GetX() + base->GetWidth() + base->GetRange();
      for (auto it = enemies.begin(); it != enemies.end(); it++)
        if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right) {
          it->Freeze(2000);
          it->Stun(2000);
        }
      FireTime = true;
    }
    return Fire();
  }

  bool Fire() {
    if (movedDistance > 300) {
      movedDistance = 0;
      return false;
    }
    window.Draw(base.get());
    if (base->destination == LEFT)
      base->Move(-base->speed, 0);
    else
      base->Move(base->speed, 0);
    movedDistance += base->speed;
    for (auto it = enemies.begin(); it != enemies.end(); it++) {
      if (it->CheckCollision(base.get()) && !it->damage.UnderEffect()) {
        wchar_t text[5];
        wsprintf(text, L"%d", GetDamage());
        damageString.push_back(DrawSomeTime(std::make_shared<se::String>(se::String(text, font, it->GetX()+it->GetWidth()+2, it->GetY()+it->GetHeight(), se::Color(1.0f, 1.0f, 1.0f), false)), 1000));
        it->DamageHim(GetDamage());
      }
    }
    return true;
  }

  bool FireTime;
  int movedDistance;
};

class TwoIceMeteor : public Meteor {
  std::shared_ptr<Meteor> base;
public:
  TwoIceMeteor(Meteor *meteor) : base(meteor) {range = 200;countOfFrames = 0;falling = true;}

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    if (base->operation())
      return true;
    if (falling) {
      window.Draw(base.get());
      int left = base->GetX() - base->GetRange();
      int right = base->GetX() + base->GetWidth() + base->GetRange();
      for (auto it = enemies.begin(); it != enemies.end(); it++) {
        if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right) {
          it->Freeze(2000);
        }
      }
      falling = false;
    }
    if (!iceFromLandImage.IsValid()) {
      iceFromLandImage.LoadFromFile("img\\ice_from_lang.png");
      iceFromLand.SetImage(iceFromLandImage);
      iceFromLand.SetY(base->GetY() - 42);
    }
    iceFromLand.Move(0, 21);
    int left = base->GetX() - GetRange();
    int right = base->GetX() + base->GetWidth() + GetRange();
    if (countOfFrames == 2) {
      for (auto it = enemies.begin(); it != enemies.end(); it++)
        if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right)
          it->DamageHim(25);
      return false;
    }
    for (int i = left; i < right; i+=21) {
      iceFromLand.SetX(i);
      window.Draw(&iceFromLand);
    }
    countOfFrames++;
    return true;
  }

  se::Sprite iceFromLand;
  se::Image iceFromLandImage;
  int countOfFrames;
  bool falling;
};

class MeteorFactory {
public:
  MeteorFactory() {}

  static std::shared_ptr<Meteor> MakeMeteor(tagIMPR impr) {
    if (impr.k1 == 1 && impr.k2 == 0 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new OneFireMeteor(new BaseMeteor()));
    else if (impr.k1 == 0 && impr.k2 == 1 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new OneIceMeteor(new BaseMeteor()));
    else if (impr.k1 == 1 && impr.k2 == 1 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new OneFireAndOneIceMeteor(new BaseMeteor()));
    else if (impr.k1 == 0 && impr.k2 == 0 && impr.k3 == 1)
      return std::shared_ptr<Meteor>(new OneLightMeteor(new BaseMeteor()));
    else if (impr.k1 == 1 && impr.k2 == 0 && impr.k3 == 1)
      return std::shared_ptr<Meteor>(new OneFireAndOneLightMeteor(new BaseMeteor()));
    else if (impr.k1 == 0 && impr.k2 == 1 && impr.k3 == 1)
      return std::shared_ptr<Meteor>(new OneIceAndOneLightMeteor(new BaseMeteor()));
    else if (impr.k1 == 1 && impr.k2 == 1 && impr.k3 == 1)
      return std::shared_ptr<Meteor>(new OneFireAndOneIceAndOneLightMeteor(new BaseMeteor()));
    else if (impr.k1 == 0 && impr.k2 == 2 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new TwoIceMeteor(new BaseMeteor()));
    else
      return std::shared_ptr<Meteor>(new BaseMeteor());
  }
};