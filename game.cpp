#include "Window.hpp"
#include "Sprite.hpp"

#include "KeySphere.h"
#include "Meteor.h"
#include "Player.h"

#include <utility>
#include <vector>

std::pair<KeySphere, Skill *> skills;

bool CheckCollision(PhysicsObject& first, PhysicsObject &second) {
	unsigned int width = first.GetX() + first.GetWidth();
	unsigned int height = first.GetY() + first.GetHeight();
	unsigned int aWidth = second.GetX() + second.GetWidth();
	unsigned int aHeight = second.GetY() + second.GetHeight();

	// Check collision between two objects

  //return (first.GetY() < aHeight && width > second.GetX());
	return (first.GetX() < aWidth && first.GetY() < aHeight && second.GetX() < width && second.GetY() < height);
}

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
  Player player(50, 0, 0);
  Player enemy(200, 0, 0);
  player.SetImage(playerImg);
  enemy.SetImage(playerImg);
  
  se::Sprite spheres[3];
  for (int i = 0; i < 3; i++)
    spheres[i].SetY(window.GetHeight()-50);
  
  se::Image images[3];
  images[0].LoadFromFile("img\\fire.png");
  images[1].LoadFromFile("img\\ice.png");
  images[2].LoadFromFile("img\\lighting.png");
  
  int castType;
  bool k1p;
  bool k2p;
  bool k3p;
  k1p = k2p = k3p = false;

  bool castingSkill = false;
  bool isDamaged = false;

  while (window.IsOpened()) {
    window.ProcessEvents();
    
    castType = 0;

    // Handle keys here
    if (currentSphere.IsFull()) {
      if (input.IsKeyPressed(VK_SPACE))
        castingSkill = true;
    }
    else {
      if (input.IsKeyPressed(49) && !k1p) { currentSphere.k1++; castType = 1; k1p = true; }
      else if (input.IsKeyPressed(50) && !k2p) { currentSphere.k2++; castType = 2; k2p = true; }
      else if (input.IsKeyPressed(51) && !k3p) { currentSphere.k3++; castType = 3; k3p = true;}

      if (!input.IsKeyPressed(49)) k1p = false;
      if (!input.IsKeyPressed(50)) k2p = false;
      if (!input.IsKeyPressed(51)) k3p = false;
    }

    if (input.IsKeyPressed('W')) player.Jump();
    if (input.IsKeyPressed('A')) player.Move(-1, 0);
    if (input.IsKeyPressed('D')) player.Move(1, 0);

    // Key-hack for testing
    if (input.IsKeyPressed(VK_F1)) { currentSphere.k1 = 2; currentSphere.k2 = 1; currentSphere.k3 = 0; castingSkill = true; };

    if (castType != 0) {
      int count = currentSphere.GetCount()-1;
      spheres[count].SetImage(images[castType-1]);
      spheres[count].SetX(50*count);
    }

    player.Tick();

    window.Clear(se::Color(1.0f, 1.0f, 1.0f));

    // Drawing player
    window.Draw(&player);

    if (enemy.IsAlive())
	    window.Draw(&enemy);
    
    // Drawing spheres
    for (int i = 0; i < currentSphere.GetCount(); i++)
      window.Draw(&spheres[i]);

    // Drawing skill
    if (castingSkill) {
      if (skills.first == currentSphere) {
        skills.second->Cast(player);
      }
      currentSphere.Clear();
      castingSkill = isDamaged = false;
    }

    if (skills.second->casting) {
      skills.second->Tick(window);
	    if (CheckCollision(enemy, *skills.second) && enemy.IsAlive() && !isDamaged) {
        enemy.DamageHim(skills.second->GetDamage());
        isDamaged = true;
      }
    }

    window.Display();
    Sleep(15);
  }

  DeinitSkills();
  return 0;
}