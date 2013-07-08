#pragma once

#include "Renderable.hpp"
#include "Image.hpp"

#include <vector>

class Animation : public se::Renderable {
public:
  Animation() : se::Renderable(), currentFrame(0), speed(500), test(0), loop(false), ended(false) {}
  
  Animation(int x, int y, int width, int height, DWORD speed, bool loop, se::Color color, bool isFixed) : se::Renderable(x, y, width, height, color, isFixed), currentFrame(0), speed(speed), test(0), loop(loop), ended(false) {}
  
  void AddFrame(const std::string &image) {
    se::Image imageS;
    if (imageS.LoadFromFile(image))
      images.push_back(imageS);
  }

  void SetSpeed(int newSpeed) {
    speed = newSpeed;
  }

  void SetLoop(bool loop) {
    this->loop = loop;
  }

  int GetSpeed() const {
    return speed;
  }

  int GetCountOfFrames() {
    return images.size();
  }

  bool IsEnded() const {
    return ended;
  }

  void SetCurrentFrame(int curFrame) {
    currentFrame = curFrame;
    ended = false;
  }

private:
  void Render() const {
    if (ended) return ;

    int width = images[currentFrame].GetWidth();
    int height = images[currentFrame].GetHeight();

    int top = isFlippedY ? textureRect.bottom : textureRect.top;
    int left = isFlippedX ? textureRect.right : textureRect.left;
    int right = isFlippedX ? textureRect.left : textureRect.right;
    int bottom = isFlippedY ? textureRect.top : textureRect.bottom;

    if (images[currentFrame].IsValid() && (width != 0 || height != 0)) {
      glEnable(GL_TEXTURE_2D);
      images[currentFrame].BindTexture();
      glBegin(GL_QUADS);
        glTexCoord2f(left, top);
        glVertex2f(0, 0);

        glTexCoord2f(right, top);
        glVertex2f(width, 0);

        glTexCoord2f(right, bottom);
        glVertex2f(width, height);

        glTexCoord2f(left, bottom);
        glVertex2f(0, height);
      glEnd();
    }
    else {
      glDisable(GL_TEXTURE_2D);
      glBegin(GL_QUADS);
        glVertex2f(-width, -height);
        glVertex2f(width, -height);
        glVertex2f(width, height);
        glVertex2f(-width, height);
      glEnd();
    }

    if (GetTickCount() - test > speed) {
      if (currentFrame + 1 >= images.size()) {
        if (loop) currentFrame = 0;
        else ended = true;
      }
      else
        currentFrame += 1;
      test = GetTickCount();
    }
  }

  std::vector<se::Image> images;
  mutable int currentFrame;
  DWORD speed;
  mutable DWORD test;
  bool loop;
  mutable bool ended;
};