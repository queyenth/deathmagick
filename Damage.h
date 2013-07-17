#pragma once

#include <windows.h>

class Damage {
public:
  enum Type { PHYSICAL, FIRE, ICE, LIGHT, ALL };

  Damage() : type(PHYSICAL), damage(0) {}
  Damage(Type type, int damage) : type(type), damage(damage) {}

  virtual ~Damage() {}

  virtual int GetDamage() {
    return damage;
  }
  
  virtual Type GetType() {
    return type;
  }

  Type type;
  int damage;
};