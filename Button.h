#pragma once

#include "Sprite.hpp"

class Button : public se::Sprite {
public:
  Button(se::Image &image, void (*callbackFunc)(void *data), int x, int y, int width, int height, se::Color color) : se::Sprite(x, y, width, height, color, true) {
    this->image = image;
    SetCallback(callbackFunc);
  }
  Button() : se::Sprite() {}

  bool OnHover(unsigned int mouseX, unsigned int mouseY) {
    return (x <= mouseX && mouseX <= x+GetWidth() && y <= mouseY && mouseY <= y+GetHeight());
  }
  
  void OnClick(void *data) {
    callbackFunc(data);
  }

  void SetCallback(void (*callbackFunc)(void *data)) {
    this->callbackFunc = callbackFunc;
  }

private:
  void (*callbackFunc)(void *data);
};