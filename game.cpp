#include "Window.hpp"
#include "Sprite.hpp"

#include "KeySphere.h"
#include "Meteor.h"
#include "Player.h"
#include "String.hpp"

#include <utility>
#include <vector>
#include <ctime>

std::pair<KeySphere, Skill *> skills;

bool CheckCollision(PhysicsObject& first, PhysicsObject &second) {
	unsigned int width = first.GetX() + first.GetWidth();
	unsigned int height = first.GetY() + first.GetHeight();
	unsigned int aWidth = second.GetX() + second.GetWidth();
	unsigned int aHeight = second.GetY() + second.GetHeight();

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
  srand(time(NULL));
  se::Window window(L"Test");

  const se::Input &input = window.GetInput();
  se::Camera &camera = window.GetCamera();
  KeySphere currentSphere;

  se::String testString;
  testString.SetFont(window.GetDC(), L"Courier New");
  
  se::Image playerImg;
  playerImg.LoadFromFile("img\\player.png");
  Player player(50, 0, 0);
  Player enemies[10];
  for (int i = 0; i < 10; i++) {
    enemies[i].SetX((i+1)*80);
    enemies[i].SetImage(playerImg);
  }
  player.SetImage(playerImg);
  
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
    if (input.IsKeyPressed('A')) { player.Move(-1, 0); player.FlipX(true); }
    if (input.IsKeyPressed('D')) { player.Move(1, 0); player.FlipX(false); }

    if (player.GetX() >= window.GetWidth()/2 + camera.GetViewX()) camera.OffsetViewByX(player.GetX() - window.GetWidth()/2);
    else if (player.GetX() <= window.GetWidth()/2) camera.SetViewPoint(se::Vertex2D(0, 0));

    // Key-hack for testing
    if (input.IsKeyPressed(VK_F1)) { currentSphere.k1 = 2; currentSphere.k2 = 1; currentSphere.k3 = 0; castingSkill = true; };

    if (castType != 0) {
      int count = currentSphere.GetCount()-1;
      spheres[count].SetImage(images[castType-1]);
      spheres[count].SetX(50*count);
    }

    player.Tick();

    window.Clear(se::Color(0.0f, 0.0f, 0.0f));

    // Drawing player
    window.Draw(&player);

    for (int i = 0; i < 10; i++)
      if (enemies[i].IsAlive())
	      window.Draw(&enemies[i]);
    
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
      for (int i = 0; i < 10; i++)
	      if (CheckCollision(enemies[i], *skills.second) && enemies[i].IsAlive() && !isDamaged) {
          wchar_t text[5];
          wsprintf(text, L"%d", skills.second->GetDamage());
          enemies[i].DamageHim(skills.second->GetDamage());
          testString.SetText(text);
          testString.SetX(enemies[i].GetX()+enemies[i].GetWidth()-camera.GetViewX());
          testString.SetY(enemies[i].GetY()+enemies[i].GetHeight()-camera.GetViewY()+10);
          testString.Render();
          isDamaged = true;
        }
    }

    window.Display();
    Sleep(15);
  }

  DeinitSkills();
  return 0;
}