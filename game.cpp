#include "Window.hpp"
#include "Sprite.hpp"

#include "KeySphere.h"
#include "Meteor.h"
#include "Player.h"

#include <utility>
#include <vector>

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

  const se::Input &input = window.GetInput();
  KeySphere currentSphere;
  se::Image playerImg;
  playerImg.LoadFromFile("img\\player.png");
  Player player(50, 50, 0);
  player.SetImage(playerImg);
  
  se::Sprite spheres[3];
  
  se::Image images[3];
  images[0].LoadFromFile("img\\fire.png");
  images[1].LoadFromFile("img\\ice.png");
  images[2].LoadFromFile("img\\lighting.png");
  
  int castType;

  bool castingSkill = false;
  
  std::vector<Skill *> skillsOnFrame;

  while (window.IsOpened()) {
    window.ProcessEvents();
    
    castType = 0;

    // Handle keys here
    if (currentSphere.IsFull()) {
      if (input.IsKeyPressed(VK_SPACE))
        castingSkill = true;
    }
    else {
      if (input.IsKeyPressed(49)) { currentSphere.k1++; castType = 1; }
      else if (input.IsKeyPressed(50)) { currentSphere.k2++; castType = 2; }
      else if (input.IsKeyPressed(51)) { currentSphere.k3++; castType = 3; }
    }
    if (input.IsKeyPressed('W')) player.Move(0, 1);
    if (input.IsKeyPressed('A')) player.Move(-1, 0);
    if (input.IsKeyPressed('S')) player.Move(0, -1);
    if (input.IsKeyPressed('D')) player.Move(1, 0);

    // Key-hack for testing
    if (input.IsKeyPressed(VK_F1)) { currentSphere.k1 = 2; currentSphere.k2 = 1; currentSphere.k3 = 0; };

    if (castType != 0) {
      int count = currentSphere.GetCount()-1;
      spheres[count].SetImage(images[castType-1]);
      spheres[count].SetX(50*count);
    }

    window.Clear(se::Color(1.0f, 1.0f, 1.0f));

    // Drawing player
    window.Draw(&player);
    
    // Drawing spheres
    for (int i = 0; i < currentSphere.GetCount(); i++)
      window.Draw(&spheres[i]);

    // Drawing skill
    if (castingSkill) {
      if (skills.first == currentSphere) {
        skills.second->Cast(player);
        skillsOnFrame.push_back(skills.second);
      }
      currentSphere.Clear();
      castingSkill = false;
    }

    for (std::vector<Skill *>::iterator i = skillsOnFrame.begin(); i != skillsOnFrame.end(); i++) {
      if ((*i)->casting)
        (*i)->Tick(window);
      else
        skillsOnFrame.erase(i);
    }

    window.Display();
    Sleep(15);
  }

  DeinitSkills();
  return 0;
}