#include "Window.hpp"
#include "Sprite.hpp"

#include "KeySphere.h"
#include "Meteor.h"
#include "Player.h"
#include "String.hpp"

#include <utility>
#include <vector>
#include <ctime>
#include <algorithm>


class DrawSomeTime {
public:
  DrawSomeTime(se::Renderable *entity, DWORD time) {
    SetEntity(entity);
    this->time = time;
  }

  DrawSomeTime() {
    entity = nullptr;
    time = 0;
  }

  ~DrawSomeTime() {
    
  }

  void SetEntity(se::Renderable *entity) {
    this->entity = entity;
    firstTime = GetTickCount();
  }

  se::Renderable *entity;
  DWORD time;
  DWORD firstTime;
};


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
  srand(time(NULL));
  se::Window window(L"Untitled Game", 1024, 768, false);

  const se::Input &input = window.GetInput();
  se::Camera &camera = window.GetCamera();
  KeySphere currentSphere;

  std::shared_ptr<se::Font> font(new se::Font(window.GetDC(), L"Courier New", 18));
  
  se::Image playerImg;
  playerImg.LoadFromFile("img\\player.png");
  Player player(50, window.GetHeight()/3, 0);
  vector<Player> enemies;
  for (int i = 0; i < 10; i++) {
    Player enemy;
    enemy.SetX((i+1)*80);
    enemy.SetImage(playerImg);
    enemy.SetY(window.GetHeight()/2);
    enemies.push_back(enemy);
  }
  player.SetImage(playerImg);
  
  se::Sprite spheres[3];
  for (int i = 0; i < 3; i++) {
    spheres[i].SetY(window.GetHeight()-50);
    spheres[i].SetFixedMode(true);
  }
  
  se::Image images[3];
  images[0].LoadFromFile("img\\f1.png");
  images[1].LoadFromFile("img\\l1.png");
  images[2].LoadFromFile("img\\m1.png");
  
  int castType;
  bool k1p;
  bool k2p;
  bool k3p;
  k1p = k2p = k3p = false;

  bool castingSkill = false;
  bool isDamaged = false;

  se::Sprite floor(0, 0, window.GetWidth(), window.GetHeight()/4, se::Color(0.5f, 0.5f, 0.5f), true);

  std::vector<DrawSomeTime> damageString;

  // FIXME: Improve gameloop :3
  while (window.IsOpened()) {
    window.ProcessEvents();

    if (!window.IsActive()) continue;
    
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
    if (input.IsKeyPressed('A')) { player.Move(-3, 0); player.FlipX(true); }
    if (input.IsKeyPressed('D')) { player.Move(3, 0); player.FlipX(false); }
    if (input.IsKeyPressed(VK_ESCAPE)) { PostQuitMessage(0); }

    unsigned int middle = window.GetWidth()/2 + camera.GetViewX();
    if (player.GetX() <= window.GetWidth()/2)
      camera.SetViewPoint(se::Vertex2D(0, 0));
    else
      camera.OffsetViewByX(player.GetX() - middle);

    // Key-hack for testing
    if (input.IsKeyPressed(VK_F1)) { currentSphere.k1 = 2; currentSphere.k2 = 1; currentSphere.k3 = 0; castingSkill = true; };

    if (castType != 0) {
      int count = currentSphere.GetCount()-1;
      spheres[count].SetImage(images[castType-1]);
      spheres[count].SetX(50*count);
    }

    player.Tick(1, &floor);

    for (auto it = enemies.begin(); it != enemies.end(); it++)
      it->Tick(1, &floor);

    // TODO : Erase all dead enemies from vector [amazing stuff, but I think that it costs a lot of time]
    // TODO : Will check it later.
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Player t) { return !t.IsAlive(); }), enemies.end());
    damageString.erase(std::remove_if(damageString.begin(), damageString.end(), [](DrawSomeTime t) { return GetTickCount() - t.firstTime > t.time; }), damageString.end());
    
    for (auto t = enemies.begin(); t != enemies.end(); t++) {
      if (GetTickCount() - t->damageTime > 2000 && t->damageTime != 0) {
        t->damageTime = 0;
        t->SetColor(se::Color(1.0f, 1.0f, 1.0f));
      }
    }

    window.Clear();

    // Drawing player
    window.Draw(&player);

    // Drawing floor
    window.Draw(&floor);

    // Drawing enemies
    for (auto it = enemies.begin(); it != enemies.end(); it++) {
	    window.Draw(&(*it));
      it->DrawHealth(window);
    }
    
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

    // If skill casting draw skill, and check on collision
    if (skills.second->casting) {
      skills.second->Tick(window, 1, &floor);
      if (!skills.second->casting) {
        int left = skills.second->GetX() - skills.second->GetRange();
        int right = skills.second->GetX() + skills.second->GetWidth() + skills.second->GetRange();
        for (auto it = enemies.begin(); it != enemies.end(); it++)
          if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right) {
            wchar_t text[5];
            wsprintf(text, L"%d", skills.second->GetDamage());
            damageString.push_back(DrawSomeTime(new se::String(text, font.get(), it->GetX()+it->GetWidth()+2, it->GetY()+it->GetHeight(), se::Color(0.0f, 0.0f, 0.0f), false), 1000));

            it->DamageHim(skills.second->GetDamage());
          }
      }
    }

    //window.Draw(&testString);
    for (auto it = damageString.begin(); it != damageString.end(); it++)
      if (it->entity != nullptr)
        window.Draw(it->entity);

    window.Display();

    // For 60 FPS
    Sleep(15);
  }

  DeinitSkills();
  return 0;
}