#include "Window.hpp"
#include "KeySphere.h"
#include "Meteor.h"

#include <utility>

std::pair<KeySphere, Skill *> skills;

void InitSkills() {
  // Meteor
  skills.first = KeySphere(2, 1, 0);
  skills.second = new Meteor();
}

void DeinitSkills() {
  delete skills.second;
}

int main() {
  InitSkills();
  se::Window window(L"Test");

  se::Input &input = window.GetInput();
  KeySphere currentSphere;

  while (window.IsOpened()) {
    window.ProcessEvents();

    // Handle keys here
    if (input.IsKeyPressed(49)) currentSphere.k1++;
    else if (input.IsKeyPressed(50)) currentSphere.k2++;
    else if (input.IsKeyPressed(51)) currentSphere.k3++;

    window.Clear();

    // Drawing player

    // Drawing skill
    if (currentSphere.IsFull()) {
      if (skills.first == currentSphere)
        window.Draw(skills.second);
      currentSphere.Clear();
    }

    window.Display();
  }

  DeinitSkills();
  return 0;
}