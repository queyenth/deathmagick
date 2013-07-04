#pragma once

#include <windows.h>

#include "Color.hpp"

class Effect {
public:
  Effect(se::Color effectColor)
    : effectColor(effectColor), underEffect(false) {}
  bool UnderEffect() {
    return underEffect;
  }

  void SetLong(DWORD howLong) {
    this->howLong = howLong;
  }

  void MakeEffect() {
    if (!underEffect) {
      underEffect = true;
      firstTime = GetTickCount();
    }
  }

  bool CheckEffect() {
    if (GetTickCount() - howLong > firstTime) {
      underEffect = false;
    }
    return underEffect;
  }

  se::Color GetColor() const {
    return effectColor;
  }

private:
  DWORD firstTime;
  DWORD howLong;
  bool underEffect;
  se::Color effectColor;
};