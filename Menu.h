#pragma once

#include "GlobalObject.h"
#include "Button.h"

static se::String playString, loadString, arenaString, settingsString, quitString;
static int currentSet;
static bool pressedUp, pressedDown;

void InitMenuImages() {
  playString = se::String("Play", menuFont, window.GetWidth()/2+150, window.GetHeight() - window.GetHeight()/3, se::Color(), true);
  loadString = se::String("Load", menuFont, window.GetWidth()/2+150, playString.GetY() - 50, se::Color(), true);
  arenaString = se::String("Arena", menuFont, window.GetWidth()/2+150, loadString.GetY() - 50, se::Color(), true);
  settingsString = se::String("Settings", menuFont, window.GetWidth()/2+150, arenaString.GetY() - 50, se::Color(), true);
  quitString = se::String("Quit", menuFont, window.GetWidth()/2+150, settingsString.GetY() - 50, se::Color(), true);
  backimage.LoadFromFile("img\\back.png");
  backMenu.SetImage(backimage);
  backMenu.SetX(0);
  backMenu.SetY(0);
  backMenu.SetWidth(window.GetWidth());
  backMenu.SetHeight(window.GetHeight());
  backMenu.SetFixedMode(true);
  arrowImg.LoadFromFile("img\\arrow.png");
  arrow.SetImage(arrowImg);
  arrow.SetX(playString.GetX()-arrow.GetWidth()/2);
  arrow.SetY(playString.GetY());
  arrow.SetFixedMode(true);
  pressedUp = pressedDown = false;
  currentSet = 0;
}

void DrawMenu() {
  arrow.SetX(window.GetWidth()/2+150 - arrow.GetWidth()/2);
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
      currentState = SETTINGS;
      break;
    case 4:
      currentState = QUIT;
      break;
    }
  }
  else {
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

    int x = window.GetWidth()/2+150;
    playString.SetX(x);
    loadString.SetX(x);
    arenaString.SetX(x);
    settingsString.SetX(x);
    quitString.SetX(x);

    x = arrow.GetX() + arrow.GetWidth();
    switch (currentSet) {
    case 0:
      arrow.SetY(playString.GetY());
      playString.SetX(x);
      break;
    case 1:
      arrow.SetY(loadString.GetY());
      loadString.SetX(x);
      break;
    case 2:
      arrow.SetY(arenaString.GetY());
      arenaString.SetX(x);
      break;
    case 3:
      arrow.SetY(settingsString.GetY());
      settingsString.SetX(x);
      break;
    case 4:
      arrow.SetY(quitString.GetY());
      quitString.SetX(x);
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