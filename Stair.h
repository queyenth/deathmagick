#pragma once

class Stair {
public:
  Stair(int count=1, int x=0, int y=0) : count(count), x(x), startY(y) {

  }
  
  virtual ~Stair() {
    
  }

  int count;
  int startY;
  int x;
};