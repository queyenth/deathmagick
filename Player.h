#pragma once

#include "Renderable.hpp"

class Player : public se::Renderable {
public:
  Player() {}
  virtual ~Player() {}
private:
  void Render() const {}
  unsigned int experience;
};