#pragma once

class KeySphere {
public:
  KeySphere() {
    Clear();
  }

  KeySphere(int k1, int k2, int k3) {
    this->k1 = k1;
    this->k2 = k2;
    this->k3 = k3;
  }

  ~KeySphere() {

  }

  bool IsFull() {
    return k1 + k2 + k3 == 3;
  }

  int GetCount() {
    return k1 + k2 + k3;
  }

  void Clear() {
    k1 = k2 = k3 = 0;
  }

  bool operator==(const KeySphere &anotherSphere) {
    if (this->k1 == anotherSphere.k1 &&
      this->k2 == anotherSphere.k2 &&
      this->k3 == anotherSphere.k3 &&
      this->IsFull())
      return true;
    else
      return false;
  }

  int k1;
  int k2;
  int k3;
};