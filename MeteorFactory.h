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
        it->Freeze(5000);
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
        it->Freeze(5000);
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
        it->Freeze(5000);
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
          it->Freeze(5000);
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
          it->Freeze(5000);
        }
      }
      falling = false;
    }
    if (!iceFromLandImage.IsValid()) {
      iceFromLandImage.LoadFromFile("img\\ice_from_lang.png");
      iceFromLand.SetImage(iceFromLandImage);
      iceFromLand.SetY(base->GetY() - 21);
    }
    iceFromLand.Move(0, 1);
    int left = base->GetX() - GetRange();
    int right = base->GetX() + base->GetWidth() + GetRange();
    if (countOfFrames == 21) {
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

class TwoLightMeteor : public Meteor {
  std::shared_ptr<Meteor> base;
public:
  TwoLightMeteor(Meteor *meteor) : base(meteor) {}

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    static int countOfMeteors = 0;
    static DWORD lastMeteor;
    static bool waitingNew = false;
    if (waitingNew) {
      if (GetTickCount() - lastMeteor > 500) {
        base->Cast(player);
        countOfMeteors++;
        waitingNew = false;
      }
      return true;
    }
    if (countOfMeteors != 3) {
      base->speed = 8;
      if (base->operation()) {
        return true;
      }
      else
        waitingNew = true;
      window.Draw(base.get());
      int left = GetX() - GetRange();
      int right = base->GetX() + base->GetWidth() + base->GetRange();
      for (auto it = enemies.begin(); it != enemies.end(); it++)
        if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right)
          it->Stun(2000);
      lastMeteor = GetTickCount();
      return true;
    }
    countOfMeteors = 0;
    waitingNew = false;
    return false;
  }

};

class TwoIceAndOneFireMeteor : public Meteor {
  std::shared_ptr<Meteor> base;
public:
  TwoIceAndOneFireMeteor(Meteor *base) : base(base) {range = 200; countOfFrames = 0; falling = true; movedDistance = 0; iceMaked = false; leftIce = rightIce = 0;}

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
          it->Freeze(5000);
        }
      }
      falling = false;
      iceMaked = true;
    }
    else if (iceMaked) {
      if (!iceFromLandImage.IsValid()) {
        iceFromLandImage.LoadFromFile("img\\ice_from_lang.png");
        iceFromLand.SetImage(iceFromLandImage);
        iceFromLand.SetY(base->GetY() - 21);
      }
    
      if (leftIce == rightIce && rightIce == 0) {
        leftIce = base->GetX() - GetRange();
        rightIce = base->GetX() + base->GetWidth() + GetRange();
      }
      
      for (int i = leftIce; i < rightIce; i+=21) {
        iceFromLand.SetX(i);
        window.Draw(&iceFromLand);
      }
    
      iceFromLand.Move(0, 1);
      if (countOfFrames == 21) {
        for (auto it = enemies.begin(); it != enemies.end(); it++)
          if (leftIce <= it->GetX() && it->GetX() + it->GetWidth() <= rightIce)
            it->DamageHim(25);
        iceMaked = false;
      }
      countOfFrames++;
    }
    if (movedDistance > 300) return false;
    else {
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
    }
    return true;
  }

  se::Sprite iceFromLand;
  se::Image iceFromLandImage;
  int countOfFrames;
  bool falling;
  bool iceMaked;
  int movedDistance;
  int leftIce;
  int rightIce;
};

class TwoIceAndOneLightMeteor : public Meteor {
  std::shared_ptr<Meteor> base;
public:
  TwoIceAndOneLightMeteor(Meteor *base) : base(base) {light = ice = false; countOfFrames = 0; falling = true; range = 200;}

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    base->speed = 8;
    if (!light && !ice) {
      if (base->operation())
        return true;
      else
        light = true;
    }
    if (light) {
      window.Draw(base.get());
      int left = base->GetX() - base->GetRange();
      int right = base->GetX() + base->GetWidth() + base->GetRange();
      for (auto it = enemies.begin(); it != enemies.end(); it++)
        if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right)
          it->Stun(2000);
      ice = true;
      light = false;
    }
    else if (ice) {
      if (falling) {
        window.Draw(base.get());
        int left = base->GetX() - base->GetRange();
        int right = base->GetX() + base->GetWidth() + base->GetRange();
        for (auto it = enemies.begin(); it != enemies.end(); it++) {
          if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right) {
            it->Freeze(5000);
          }
        }
        falling = false;
      }
      if (!iceFromLandImage.IsValid()) {
        iceFromLandImage.LoadFromFile("img\\ice_from_lang.png");
        iceFromLand.SetImage(iceFromLandImage);
        iceFromLand.SetY(base->GetY() - 21);
      }
      iceFromLand.Move(0, 1);
      int left = base->GetX() - GetRange();
      int right = base->GetX() + base->GetWidth() + GetRange();
      if (countOfFrames == 21) {
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
    return true;
  }

  bool light;
  bool ice;
  bool falling;
  int countOfFrames;
  se::Sprite iceFromLand;
  se::Image iceFromLandImage;

};

class TwoLightAndOneFireMeteor : public Meteor {
  BaseMeteor meteors[3];
  int movedDistance[3];
  bool falled[3];
  bool waitingNew;
  bool createdNew;
  int countOfMeteors;
  DWORD lastMeteor;
public:
  TwoLightAndOneFireMeteor() { waitingNew = true; movedDistance[0] = movedDistance[1] = movedDistance[2] = 0; lastMeteor = 0; countOfMeteors = 0; createdNew = falled[0] = falled[1] = falled[2] = false;}

  virtual bool operation() override {
    // Если нужен новый метеорит - создать его
    if (waitingNew) {
      if (GetTickCount() - lastMeteor > 500 && countOfMeteors < 3) {
        meteors[countOfMeteors].Cast(player);
        waitingNew = false;
        createdNew = true;
      }
    }
    // Если создан новый метеорит, нужно запустить его
    if (createdNew && countOfMeteors < 3) {
      Meteor *meteor = &meteors[countOfMeteors];
      meteor->speed = 8;
      // Если долетел до земли - станим всех вокруг
      if (!meteor->operation()) {
        int left = GetX() - GetRange();
        int right = meteor->GetX() + meteor->GetWidth() + meteor->GetRange();
        for (auto it = enemies.begin(); it != enemies.end(); it++)
          if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right)
            it->Stun(1000);
        falled[countOfMeteors] = true;
        lastMeteor = GetTickCount();
        countOfMeteors++;
        waitingNew = true;
      }
    }
    // Тем временем, нужно каждый упавший метеорит пускаааать по земле
    for (int i = 0; i < 3; i++) {
      if (movedDistance[i] <= 300 && falled[i]) {
        window.Draw(&meteors[i]);
        if (meteors[i].destination == LEFT)
          meteors[i].Move(-meteors[i].speed, 0);
        else
          meteors[i].Move(meteors[i].speed, 0);
        movedDistance[i] += meteors[i].speed;
        for (auto it = enemies.begin(); it != enemies.end(); it++) {
          if (it->CheckCollision(&meteors[i]) && !it->damage.UnderEffect()) {
            wchar_t text[5];
            wsprintf(text, L"%d", GetDamage());
            damageString.push_back(DrawSomeTime(std::make_shared<se::String>(se::String(text, font, it->GetX()+it->GetWidth()+2, it->GetY()+it->GetHeight(), se::Color(1.0f, 1.0f, 1.0f), false)), 1000));
            it->DamageHim(GetDamage());
          }
        }
      }
    }
    // Скилл заканчивается, когда все метеориты запущены, и все метеориты пролетели уже
    return !(movedDistance[0] > 300 && movedDistance[1] > 300 && movedDistance[2] > 300);
  }
};

class TwoLightAndOneIceMeteor : public Meteor {
  std::shared_ptr<Meteor> base;
  int countOfMeteors;
  DWORD lastMeteor;
  bool waitingNew;
public:
  TwoLightAndOneIceMeteor(Meteor *base) : base(base) {lastMeteor = 0; countOfMeteors = 0; waitingNew = false;}

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    if (waitingNew) {
      if (GetTickCount() - lastMeteor > 500) {
        base->Cast(player);
        countOfMeteors++;
        waitingNew = false;
      }
      return true;
    }
    if (countOfMeteors != 3) {
      base->speed = 8;
      if (base->operation()) {
        return true;
      }
      else
        waitingNew = true;
      window.Draw(base.get());
      int left = GetX() - GetRange();
      int right = base->GetX() + base->GetWidth() + base->GetRange();
      for (auto it = enemies.begin(); it != enemies.end(); it++)
        if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right) {
          it->Stun(2000);
          it->Freeze(5000);
        }
      lastMeteor = GetTickCount();
      return true;
    }
    countOfMeteors = 0;
    waitingNew = false;
    return false;
  }

};

class TwoFireMeteor : public Meteor {
  std::shared_ptr<Meteor> base;
public:
  TwoFireMeteor(Meteor *base) : base(base) {FireTime = false; movedDistance = 0; lastFire = 0;}

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    if (!FireTime) {
      if (base->operation())
        return true;
      FireTime = true;
    }
    if (!fireImage.IsValid()) {
      fireImage.LoadFromFile("img\\fire.png");
      fireSprite.SetImage(fireImage);
      fireSprite.SetY(base->GetY());
    }
    if (movedDistance > 300) {
      movedDistance = 0;
      return false;
    }
    window.Draw(base.get());
    if (base->GetX() - lastFire > fireSprite.GetWidth()) {
      lastFire = base->GetX();
      fireSprite.SetX(lastFire);
      damageString.push_back(DrawSomeTime(std::shared_ptr<se::Sprite>(new se::Sprite(fireSprite)), 3000));
    }
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

  se::Image fireImage;
  se::Sprite fireSprite;
  int lastFire;

};

class TwoFireAndOneLightMeteor : public Meteor {
  std::shared_ptr<Meteor> base;
public:
  TwoFireAndOneLightMeteor(Meteor *base) : base(base) {FireTime = false; movedDistance = 0; lastFire = 0;}

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    base->speed = 8;
    if (!FireTime) {
      if (base->operation())
        return true;
      int left = GetX() - GetRange();
      int right = base->GetX() + base->GetWidth() + base->GetRange();
      for (auto it = enemies.begin(); it != enemies.end(); it++)
        if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right)
          it->Stun(1000);
      FireTime = true;
    }
    if (!fireImage.IsValid()) {
      fireImage.LoadFromFile("img\\fire.png");
      fireSprite.SetImage(fireImage);
      fireSprite.SetY(base->GetY());
    }
    if (movedDistance > 300) {
      movedDistance = 0;
      return false;
    }
    window.Draw(base.get());
    if (base->GetX() - lastFire > fireSprite.GetWidth()) {
      lastFire = base->GetX();
      fireSprite.SetX(lastFire);
      damageString.push_back(DrawSomeTime(std::shared_ptr<se::Sprite>(new se::Sprite(fireSprite)), 3000));
    }
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

  se::Image fireImage;
  se::Sprite fireSprite;
  int lastFire;
};

class TwoFireAndOneIceMeteor : public Meteor {
  std::shared_ptr<Meteor> base;
public:
  TwoFireAndOneIceMeteor(Meteor *base) : base(base) {FireTime = false; movedDistance = 0; lastFire = 0;}

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    if (!FireTime) {
      if (base->operation())
        return true;
      int left = GetX() - GetRange();
      int right = base->GetX() + base->GetWidth() + base->GetRange();
      for (auto it = enemies.begin(); it != enemies.end(); it++)
        if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right)
          it->Freeze(5000);
      FireTime = true;
    }
    if (!fireImage.IsValid()) {
      fireImage.LoadFromFile("img\\fire.png");
      fireSprite.SetImage(fireImage);
      fireSprite.SetY(base->GetY());
    }
    if (movedDistance > 300) {
      movedDistance = 0;
      return false;
    }
    window.Draw(base.get());
    if (base->GetX() - lastFire > fireSprite.GetWidth()) {
      lastFire = base->GetX();
      fireSprite.SetX(lastFire);
      damageString.push_back(DrawSomeTime(std::shared_ptr<se::Sprite>(new se::Sprite(fireSprite)), 3000));
    }
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

  se::Image fireImage;
  se::Sprite fireSprite;
  int lastFire;
};

class ThreeFireMeteor : public Meteor {
  std::shared_ptr<Meteor> base;
public:
  ThreeFireMeteor(Meteor *base) : base(base) {WaveTime = FireTime = false; movedDistance = waveTimes = lastFire = 0;}

  virtual void Cast(Player &player) override {
    base->Cast(player);
  }

  virtual bool operation() override {
    if (!FireTime) {
      if (base->operation())
        return true;
      FireTime = true;
    }
    if (WaveTime) {
      if (waveTimes == 25) {
        waveTimes = 0;
        int left = waveSprite.GetX();
        int right = waveSprite.GetX()+waveSprite.GetWidth();
        for (auto it = enemies.begin(); it != enemies.end(); it++) {
          if (left <= it->GetX() && it->GetX()+it->GetWidth() <= right) {
            damageString.push_back(DrawSomeTime(std::make_shared<se::String>(se::String(L"200", font, it->GetX()+it->GetWidth()+2, it->GetY()+it->GetHeight(), se::Color(1.0f, 1.0f, 1.0f), false)), 1000));
            it->DamageHim(200);
          }
        }
        return false;
      }
      waveSprite.SetWidth(50+waveTimes*8);
      waveSprite.SetHeight(20+waveTimes*8);
      waveSprite.SetX(base->GetX()-waveSprite.GetWidth()/2);
      waveTimes++;
      window.Draw(&waveSprite);
      return true;
    }
    if (!fireImage.IsValid()) {
      fireImage.LoadFromFile("img\\fire.png");
      fireSprite.SetImage(fireImage);
      fireSprite.SetY(base->GetY());
      waveImage.LoadFromFile("img\\sphere.png");
      waveSprite.SetImage(waveImage);
      waveSprite.SetColor(se::Color(1.0f, 1.0f, 1.0f, 0.7f));
      waveSprite.SetY(base->GetY());
    }
    if (movedDistance > 300) {
      movedDistance = 0;
      WaveTime = true;// Make boom
      return true;
    }
    window.Draw(base.get());
    if (base->GetX() - lastFire > fireSprite.GetWidth()) {
      lastFire = base->GetX();
      fireSprite.SetX(lastFire);
      damageString.push_back(DrawSomeTime(std::shared_ptr<se::Sprite>(new se::Sprite(fireSprite)), 3000));
    }
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
  bool WaveTime;
  int movedDistance;
  int waveTimes;

  se::Image fireImage;
  se::Sprite fireSprite;
  se::Image waveImage;
  se::Sprite waveSprite;
  int lastFire;
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
    else if (impr.k1 == 0 && impr.k2 == 0 && impr.k3 == 2)
      return std::shared_ptr<Meteor>(new TwoLightMeteor(new BaseMeteor()));
    else if (impr.k1 == 1 && impr.k2 == 2 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new TwoIceAndOneFireMeteor(new BaseMeteor()));
    else if (impr.k1 == 0 && impr.k2 == 2 && impr.k3 == 1)
      return std::shared_ptr<Meteor>(new TwoIceAndOneLightMeteor(new BaseMeteor()));
    else if (impr.k1 == 1 && impr.k2 == 0 && impr.k3 == 2)
      return std::shared_ptr<Meteor>(new TwoLightAndOneFireMeteor());
    else if (impr.k1 == 0 && impr.k2 == 1 && impr.k3 == 2)
      return std::shared_ptr<Meteor>(new TwoLightAndOneIceMeteor(new BaseMeteor()));
    else if (impr.k1 == 2 && impr.k2 == 0 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new TwoFireMeteor(new BaseMeteor()));
    else if (impr.k1 == 2 && impr.k2 == 0 && impr.k3 == 1)
      return std::shared_ptr<Meteor>(new TwoFireAndOneLightMeteor(new BaseMeteor()));
    else if (impr.k1 == 2 && impr.k2 == 1 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new TwoFireAndOneIceMeteor(new BaseMeteor()));
    else if (impr.k1 == 3 && impr.k2 == 0 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new ThreeFireMeteor(new BaseMeteor()));
    else
      return std::shared_ptr<Meteor>(new BaseMeteor());
  }
};