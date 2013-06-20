#pragma once

#include "GlobalObject.h"

#include "Meteor.h"

class BaseMeteor : public Meteor {
public:
  virtual void operation() override {
    for (auto i = floors.begin(); i != floors.end(); i++) {
      if ((*i)->CheckCollision(this)) {
        casting = false;
        int left = GetX() - GetRange();
        if (left <= 0) left = 0;
        int right = GetX() + GetWidth() + GetRange();
        for (auto it = enemies.begin(); it != enemies.end(); it++) {
          if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right) {
            wchar_t text[5];
            wsprintf(text, L"%d", GetDamage());
            damageString.push_back(DrawSomeTime(std::make_shared<se::String>(se::String(text, font, it->GetX()+it->GetWidth()+2, it->GetY()+it->GetHeight(), se::Color(1.0f, 1.0f, 1.0f), false)), 1000));
            it->DamageHim(GetDamage());
          }
        }
      }
    }
    window.Draw(this);
    switch (destination) {
    case LEFT:
      Move(-5, -5);
      break;
    case RIGHT:
      Move(5,-5);
      break;
    default:
      break;
    }
  }
};

class OneFireMeteor : public Meteor {
public:
  OneFireMeteor() { damage = 50; }
  virtual void operation() override {
    static bool falling = false;
    static int movedDistance = 0;
    if (falling) {
      if (movedDistance > 300) {
        casting = false;
        falling = false;
        movedDistance = 0;
      }
      else {
        window.Draw(this);
        if (destination == LEFT)
          Move(-5, 0);
        else
          Move(5, 0);
        movedDistance += 5;
        for (auto it = enemies.begin(); it != enemies.end(); it++) {
          if (it->CheckCollision(this) && it->damageTime == 0) {
            wchar_t text[5];
            wsprintf(text, L"%d", GetDamage());
            damageString.push_back(DrawSomeTime(std::make_shared<se::String>(se::String(text, font, it->GetX()+it->GetWidth()+2, it->GetY()+it->GetHeight(), se::Color(1.0f, 1.0f, 1.0f), false)), 1000));
            it->DamageHim(GetDamage());
          }
        }
      }
      return ;
    }
    for (auto i = floors.begin(); i != floors.end(); i++) {
      if ((*i)->CheckCollision(this)) {
        falling = true;
        int left = GetX() - GetRange();
        if (left <= 0) left = 0;
        int right = GetX() + GetWidth() + GetRange();
        for (auto it = enemies.begin(); it != enemies.end(); it++) {
          if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right) {
            wchar_t text[5];
            wsprintf(text, L"%d", GetDamage());
            damageString.push_back(DrawSomeTime(std::make_shared<se::String>(se::String(text, font, it->GetX()+it->GetWidth()+2, it->GetY()+it->GetHeight(), se::Color(1.0f, 1.0f, 1.0f), false)), 1000));
            it->DamageHim(GetDamage());
          }
        }
      }
    }
    window.Draw(this);
    switch (destination) {
    case LEFT:
      Move(-5, -5);
      break;
    case RIGHT:
      Move(5,-5);
      break;
    default:
      break;
    }
  }
};

class MeteorFactory {
public:
  MeteorFactory() {}
  ~MeteorFactory() {}

  static std::shared_ptr<Meteor> MakeMeteor(tagIMPR impr) {
    if (impr.k1 == 0 && impr.k2 == 0 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new BaseMeteor());
    else if (impr.k1 == 1 && impr.k2 == 0 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new OneFireMeteor());
  }
};