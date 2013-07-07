#ifdef _DEBUG
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include "Arena.h"
#include "Menu.h"
#include "GameMenu.h"
#include "SkillsMenu.h"
#include "SettingsMenu.h"

#include <ctime>

int main() {
  #ifdef _DEBUG
  _CrtMemState _ms;
  _CrtMemCheckpoint(&_ms);
  #endif

  srand(time(NULL));

  int currentSet;
  int fullscreen;
  FILE *settingsFile;
  fopen_s(&settingsFile, "config", "r");
  fscanf_s(settingsFile, "%d %d", &currentSet, &fullscreen);
  fclose(settingsFile);

  switch (currentSet) {
  case 0:
    window.SetWidth(640);
    window.SetHeight(480);
    break;
  case 1:
    window.SetWidth(800);
    window.SetHeight(600);
    break;
  case 2:
    window.SetWidth(1024);
    window.SetHeight(768);
    break;
  case 3:
    window.SetWidth(1280);
    window.SetHeight(1024);
    break;
  case 4:
    window.SetWidth(1440);
    window.SetHeight(900);
    break;
  case 5:
    window.SetWidth(1920);
    window.SetHeight(1080);
    break;
  }

  if (fullscreen) window.SetFullscreen(true);
  window.CreateUserWindow();

  currentResolution = currentSet;
  fullscreenF = fullscreen;
  
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
    case SETTINGS:
      DrawSettingsMenu();
      break;
    case MENU_INIT:
      font = new se::Font(window.GetDC(), L"Arial Cyr", 18);
      menuFont = new se::Font(window.GetDC(), L"Arial Cyr", 28);
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
  delete menuFont;
  #ifdef _DEBUG
  _CrtMemDumpAllObjectsSince(&_ms);
  #endif
  return 0;
}