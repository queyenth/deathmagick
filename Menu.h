#pragma once

#include "GlobalObject.h"
#include "Button.h"

static se::String playString, loadString, arenaString, settingsString, quitString;
static int currentSet;
static bool pressedUp, pressedDown;

void InitMenuImages() {
  playString = se::String(L"Play", menuFont, window.GetWidth()/2+150, window.GetHeight() - window.GetHeight()/3, se::Color(0.62f, 0.62f, 0.62f), true);
  loadString = se::String(L"Load", menuFont, window.GetWidth()/2+150, playString.GetY() - 50, se::Color(0.62f, 0.62f, 0.62f), true);
  arenaString = se::String(L"Arena", menuFont, window.GetWidth()/2+150, loadString.GetY() - 50, se::Color(0.62f, 0.62f, 0.62f), true);
  settingsString = se::String(L"Settings", menuFont, window.GetWidth()/2+150, arenaString.GetY() - 50, se::Color(0.62f, 0.62f, 0.62f), true);
  quitString = se::String(L"Quit", menuFont, window.GetWidth()/2+150, settingsString.GetY() - 50, se::Color(0.62f, 0.62f, 0.62f), true);
  arrowImg.LoadFromFile("img\\arrow.png");
  arrow.SetImage(arrowImg);
  arrow.SetX(playString.GetX()-arrow.GetWidth());
  arrow.SetY(playString.GetY());
  arrow.SetFixedMode(true);
  pressedUp = pressedDown = false;
  currentSet = 0;
}

void DrawMenu() {
  if (input.IsKeyPressed(VK_RETURN)) {
    switch (currentSet) {
    case 0:
      currentState = MENU;
      break;
    case 1:
      currentState = MENU;
      break;
    case 2:
      currentState = ARENA_INIT;
      break;
    case 3:
      currentState = MENU;
      break;
    case 4:
      currentState = QUIT;
      break;
    }
  }
  else {
    int late = currentSet;
    if (input.IsKeyPressed(VK_DOWN) && !pressedDown) {
      currentSet = currentSet + 1 <= 4 ? currentSet + 1 : currentSet;
      pressedDown = true;
    }
    else if (input.IsKeyPressed(VK_UP) && !pressedUp) {
      currentSet = currentSet - 1 >= 0 ? currentSet - 1 : currentSet;
      pressedUp = true;
    }
    
    if (!input.IsKeyPressed(VK_UP)) pressedUp = false;
    if (!input.IsKeyPressed(VK_DOWN)) pressedDown = false;

    switch (late) {
    case 0:
      playString.SetColor(se::Color(0.62f, 0.62f, 0.62f));
      break;
    case 1:
      loadString.SetColor(se::Color(0.62f, 0.62f, 0.62f));
      break;
    case 2:
      arenaString.SetColor(se::Color(0.62f, 0.62f, 0.62f));
      break;
    case 3:
      settingsString.SetColor(se::Color(0.62f, 0.62f, 0.62f));
      break;
    case 4:
      quitString.SetColor(se::Color(0.62f, 0.62f, 0.62f));
      break;
    }
    switch (currentSet) {
    case 0:
      arrow.SetY(playString.GetY()-14);
      playString.SetColor(se::Color(1.0f, 1.0f, 1.0f));
      break;
    case 1:
      arrow.SetY(loadString.GetY()-14);
      loadString.SetColor(se::Color(1.0f, 1.0f, 1.0f));
      break;
    case 2:
      arrow.SetY(arenaString.GetY()-14);
      arenaString.SetColor(se::Color(1.0f, 1.0f, 1.0f));
      break;
    case 3:
      arrow.SetY(settingsString.GetY()-14);
      settingsString.SetColor(se::Color(1.0f, 1.0f, 1.0f));
      break;
    case 4:
      arrow.SetY(quitString.GetY()-14);
      quitString.SetColor(se::Color(1.0f, 1.0f, 1.0f));
      break;
    }
  }

  window.Clear();

  window.Draw(&backMenu);

  window.Draw(&playString);
  window.Draw(&loadString);
  window.Draw(&arenaString);
  window.Draw(&settingsString);
  window.Draw(&quitString);

  window.Draw(&arrow);

  window.Display();
}