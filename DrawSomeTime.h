#pragma once

#include "Renderable.hpp"

#include <memory>

template <typename value>
class DrawSomeTime {
public:
  DrawSomeTime(std::shared_ptr<value> entity, DWORD time) {
    SetEntity(entity);
    this->time = time;
  }

  DrawSomeTime() {
    entity = nullptr;
    time = 0;
  }

  ~DrawSomeTime() {
    
  }

  void SetEntity(std::shared_ptr<value> entity) {
    this->entity = entity;
    firstTime = GetTickCount();
  }

  std::shared_ptr<value> entity;
  DWORD time;
  DWORD firstTime;
};