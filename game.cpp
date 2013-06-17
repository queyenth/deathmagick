#ifdef _DEBUG
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include "Window.hpp"
#include "Sprite.hpp"
#include "KeySphere.h"
#include "Meteor.h"
#include "Player.h"
#include "String.hpp"
#include "Button.h"

#include <utility>
#include <vector>
#include <ctime>
#include <algorithm>

class DrawSomeTime {
public:
  DrawSomeTime(std::shared_ptr<se::Renderable> entity, DWORD time) {
    SetEntity(entity);
    this->time = time;
  }

  DrawSomeTime() {
    entity = nullptr;
    time = 0;
  }

  ~DrawSomeTime() {
    
  }

  void SetEntity(std::shared_ptr<se::Renderable> entity) {
    this->entity = entity;
    firstTime = GetTickCount();
  }

  std::shared_ptr<se::Renderable> entity;
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

enum GameState { MENU, PAUSE, ARENA_INIT, ARENA_PLAY, QUIT };
GameState currentState = MENU;

se::Window window(L"Untitled Game", 1024, 768, false);
const se::Input &input = window.GetInput();
se::Camera &camera = window.GetCamera();
se::Font *font = new se::Font(window.GetDC(), L"Courier New", 18);
int backgroundScroll1 = window.GetWidth()/2;
int backgroundScroll2 = window.GetWidth();
se::Image playerImg;
Player player(50, window.GetHeight()/3, 0);
vector<Player> enemies;
se::Sprite spheres[3];
se::Image images[3];
bool k1p, k2p, k3p;
bool castingSkill = false;
KeySphere currentSphere;
std::vector<se::Sprite> floors;
se::Sprite stair(880, window.GetHeight()/4);
se::Image stairImage;
se::Sprite health(0, window.GetHeight()-10, player.GetHealth(), 10, se::Color(0.8f, 0.2f, 0.2f), true);
int stairHeight;
std::vector<DrawSomeTime> damageString;
se::Sprite backgrounds[2][15];
se::Image leaf;
se::Image playImage,arenaImage,quitImage,backimage;
se::Sprite backMenu = se::Sprite(0, 0, window.GetWidth(), window.GetHeight());

void InitEnemies() {
  for (int i = 0; i < 10; i++) {
    Player enemy;
    enemy.SetX((i+1)*80);
    enemy.SetImage(playerImg);
    enemy.SetY(window.GetHeight()/2);
    enemies.push_back(enemy);
  }
}

void InitPlayer() {
  playerImg.LoadFromFile("img\\player.png");
  player.SetImage(playerImg);
}

void InitStairs() {
  stairImage.LoadFromFile("img\\stair.png");
  stair.SetImage(stairImage);
  stairHeight = floors[2].GetY()+floors[2].GetHeight()+10-window.GetHeight()/4;
}

void InitBackgrounds() {
  leaf.LoadFromFile("img\\leaf.png");
  for (int i = 0; i < 2; i++)
      for (int j = 0; j < 15; j++) {
      backgrounds[i][j].SetX(rand()%window.GetWidth());
      backgrounds[i][j].SetY(window.GetHeight()/4 + rand()%(window.GetHeight()-window.GetHeight()/4));
      backgrounds[i][j].SetImage(leaf);
      backgrounds[i][j].Rotate(rand()%360+1);
      backgrounds[i][j].SetFixedMode(true);
    }
}

void InitFloors() {
  floors.push_back(se::Sprite(0, 0, 4000, window.GetHeight()/4, se::Color(0.5f, 0.5f, 0.5f), true));
  floors.push_back(se::Sprite(250, window.GetHeight()/4, 100, 100, se::Color(0.5f, 0.5f, 0.5f), false));
  floors.push_back(se::Sprite(860, 400, 200, 50, se::Color(0.5f, 0.5f, 0.5f), false));
}

void InitSpheres() {
  for (int i = 0; i < 3; i++) {
    spheres[i].SetY(window.GetHeight()-60);
    spheres[i].SetFixedMode(true);
  }
  images[0].LoadFromFile("img\\f1.png");
  images[1].LoadFromFile("img\\l1.png");
  images[2].LoadFromFile("img\\m1.png");
  k1p = k2p = k3p = false;
}

void PlayPressed(void *data) {
  currentState = MENU;
}

void ArenaPressed(void *data) {
  currentState = ARENA_INIT;
}

void QuitPressed(void *data) {
  currentState = QUIT;
}

void InitMenuImages() {
  playImage.LoadFromFile("img\\playButton.png");
  arenaImage.LoadFromFile("img\\arenaButton.png");
  quitImage.LoadFromFile("img\\quitButton.png");
  backimage.LoadFromFile("img\\back.png");

  backMenu.SetImage(backimage);
}

void DrawMenu() {
  static Button play = Button(playImage, PlayPressed, window.GetWidth()/2-100, window.GetHeight()/2+75, 200, 50, se::Color());
  static Button arena = Button(arenaImage, ArenaPressed, window.GetWidth()/2-100, window.GetHeight()/2-25, 200, 50, se::Color());
  static Button quit = Button(quitImage, QuitPressed, window.GetWidth()/2-100, window.GetHeight()/2-125, 200, 50, se::Color());

  if (quit.OnHover(input.GetMouseX(), input.GetMouseY())) {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    play.Move(-1, -3);
    if (input.IsLeftMousePressed())
      play.OnClick(NULL);
    play.Move(1, 3);
  }
  else if (arena.OnHover(input.GetMouseX(), input.GetMouseY())) {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    arena.Move(-1, -3);
    if (input.IsLeftMousePressed())
      arena.OnClick(NULL);
    arena.Move(1, 3);
  }
  else if (play.OnHover(input.GetMouseX(), input.GetMouseY())) {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    quit.Move(-1, -3);
    if (input.IsLeftMousePressed())
      quit.OnClick(NULL);
    quit.Move(1, 3);
  }
  else {
    SetCursor(LoadCursor(NULL, IDC_ARROW));
  }

  window.Clear();

  window.Draw(&backMenu);

  window.Draw(&play);
  window.Draw(&arena);
  window.Draw(&quit);

  window.Display();
}

void DrawArena() {

  int castType = 0;

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

  if (input.IsKeyPressed('W')) {
    if (stair.GetX() <= player.GetX() && player.GetX() <= stair.GetX() + stair.GetWidth()
        && stair.GetY()-stairHeight <= player.GetY() && player.GetY() <= stair.GetY()) {
      player.inAir = Player::ONSTAIR;
    }
    else if (player.inAir == Player::ONSTAIR) {
      player.inAir = Player::STADING;
    }
    if (player.inAir == Player::ONSTAIR)
      player.Move(0, 3);
    else
      player.Jump();
  }
  if (input.IsKeyPressed('A')) {
    if (player.GetX() - 3 > 2) {
      player.TryToMove(-3, 0, floors);
      player.FlipX(true);
    }
  }
  if (input.IsKeyPressed('D')) {
    player.TryToMove(3, 0, floors);
    player.FlipX(false);
  }
  if (input.IsKeyPressed('S')) {
    if (player.inAir == Player::ONSTAIR)
      player.Move(0, -3);
  }

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
  
  player.Tick(floors);
  health.SetWidth(player.GetHealth()*2);

  // TODO : Erase all dead enemies from vector [amazing stuff, but I think that it costs a lot of time]
  // TODO : Will check it later.
  enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Player t) { return !t.IsAlive(); }), enemies.end());
  damageString.erase(std::remove_if(damageString.begin(), damageString.end(), [](DrawSomeTime t) { return GetTickCount() - t.firstTime > t.time; }), damageString.end());
  
  for (auto i = enemies.begin(); i != enemies.end(); i++) {
    i->Tick(floors);
    if (GetTickCount() - i->damageTime > 2000 && i->damageTime != 0) {
      i->damageTime = 0;
      i->SetColor(se::Color(1.0f, 1.0f, 1.0f));
    }
  }

  for (int i = 0; i < 15; i++)
    backgrounds[0][i].SetX(backgroundScroll1);
  for (int i = 0; i < 15; i++)
    backgrounds[1][i].SetX(backgroundScroll2);

  window.Clear(se::Color(0.0f, 0.0f, 0.0f));
  
  // Drawing background
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 15; j++)
      window.Draw(&backgrounds[i][j]);

  // Drawing floor
  for (auto i = floors.begin(); i != floors.end(); i++)
    window.Draw(&*i);
  
  // Drawing stairs
  for (int i = 0; i <= stairHeight; i+=10) {
    stair.SetY(window.GetHeight()/4+i);
    window.Draw(&stair);
  }

  // Drawing player
  window.Draw(&player);

  // Drawing enemies
  for (auto i = enemies.begin(); i != enemies.end(); i++) {
	  window.Draw(&*i);
    i->DrawHealth(window);
  }
    
  // Drawing spheres
  for (int i = 0; i < currentSphere.GetCount(); i++)
    window.Draw(&spheres[i]);
    
  // Drawing health bar
  window.Draw(&health);

  // Drawing skill
  if (castingSkill) {
    if (skills.first == currentSphere) {
      skills.second->Cast(player);
    }
    currentSphere.Clear();
    castingSkill = false;
  }

  // If skill casting draw skill, and check on collision
  if (skills.second->casting) {
    skills.second->Tick(window, floors);
    if (!skills.second->casting) {
      int left = skills.second->GetX() - skills.second->GetRange();
      if (left <= 0) left = 0;
      int right = skills.second->GetX() + skills.second->GetWidth() + skills.second->GetRange();
      for (auto it = enemies.begin(); it != enemies.end(); it++) {
        if (left <= it->GetX() && it->GetX() + it->GetWidth() <= right) {
          wchar_t text[5];
          wsprintf(text, L"%d", skills.second->GetDamage());
          damageString.push_back(DrawSomeTime(std::make_shared<se::String>(se::String(text, font, it->GetX()+it->GetWidth()+2, it->GetY()+it->GetHeight(), se::Color(1.0f, 1.0f, 1.0f), false)), 1000));
          it->DamageHim(skills.second->GetDamage());
        }
      }
    }
  }

  for (auto i = damageString.begin(); i != damageString.end(); i++)
    if (i->entity != nullptr)
      window.Draw(i->entity.get());
  
  window.Display();

  backgroundScroll1--;
  backgroundScroll2--;
  if (backgroundScroll1 < 0) {
    backgroundScroll1 = window.GetWidth();
  }
  if (backgroundScroll2 < 0) {
    backgroundScroll2 = window.GetWidth();
  }

  // For 60 FPS
  Sleep(15);
}

int main() {
  _CrtMemState _ms;
  _CrtMemCheckpoint(&_ms);

  InitSkills();
  InitMenuImages();
  srand(time(NULL));
  
  // FIXME: Improve gameloop :3
  while (window.IsOpened()) {
    window.ProcessEvents();

    if (!window.IsActive()) continue;
    
    switch (currentState) {
    case MENU:
      DrawMenu();
      break;
    case PAUSE:
      //DrawPause();
      break;
    case ARENA_INIT:
      InitBackgrounds();
      InitFloors();
      InitStairs();
      InitPlayer();
      InitEnemies();
      InitSpheres();
      currentState = ARENA_PLAY;
      break;
    case ARENA_PLAY:
      DrawArena();
      break;
    case QUIT:
      exit(0);
      break;
    }
  }

  DeinitSkills();
  delete font;
  _CrtMemDumpAllObjectsSince(&_ms);
  return 0;
}