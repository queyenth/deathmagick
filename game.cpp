#ifdef _DEBUG
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include "Arena.h"
#include "Menu.h"
#include "GameMenu.h"
#include "SkillsMenu.h"

#include <ctime>

int main() {
  _CrtMemState _ms;
  _CrtMemCheckpoint(&_ms);

  srand(time(NULL));
  
  // FIXME: Improve gameloop :3
  while (window.IsOpened()) {
    window.ProcessEvents();

    if (!window.IsActive()) continue;
    
    switch (currentState) {
    case ARENA_PLAY:
      DrawArena();
      break;
    case MENU:
      DrawMenu();
      break;
    case MENU_INIT:
      font = new se::Font(window.GetDC(), L"Courier New", 18);
      menuFont = new se::Font(window.GetDC(), L"Arial", 28);
      backimage.LoadFromFile("img\\back.png");
      backMenu.SetImage(backimage);
      InitMenuImages();
      currentState = MENU;
      break;
    case PAUSE:
      //DrawPause();
      break;
    case GAME_MENU:
      DrawGameMenu();
      break;
    case SKILLS:
      InitSkillsMenu();
      DrawSkills();
      break;
    case ARENA_INIT:
      InitArena();
      currentState = ARENA_PLAY;
      break;
    case ARENA_DEINIT:
      DeinitArena();
      currentState = MENU;
      break;
    case QUIT:
      exit(0);
      break;
    }
  }

  DeinitArena();
  delete font;
  _CrtMemDumpAllObjectsSince(&_ms);
  return 0;
}