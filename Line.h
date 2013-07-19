#pragma once

#include "PhysicsObject.h"

namespace se {

class Line : public PhysicsObject {
public:
  Line();
  Line(int x1, int x2, int y) : x1(x1), x2(x2), y(y) {
    SetX(x1);
    SetY(y);
    SetWidth(x2 - x1);
    SetHeight(3);
  }

  bool CheckCollision(PhysicsObject *other) const override {
    if (other->GetY() <= y+2 && other->GetX() > x1 && other->GetX() < x2) {
      other->SetY(y+2);
      return true;
    }
    return false;
  }

  int x1;
  int x2;
  int y;
private:
  void Render() const {
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
      glVertex2i(0, 0);
      glVertex2i(GetWidth(), 0);
      glVertex2i(GetWidth(), GetHeight());
      glVertex2i(0, GetHeight());
    glEnd();
  }
};

}