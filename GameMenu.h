#pragma once

#include "GlobalObject.h"

static se::String continString,skillsString,quitString1;
static se::String experience;
static bool isInitedGameMenu = false;
static int currentSet1;
extern se::Sprite backMenu;

void InitGameImages() {
  continString = se::String(L"Continue", menuFont, window.GetWidth()/2+150, window.GetHeight() - window.GetHeight()/3, se::Color(0.62f, 0.62f, 0.62f), true);
  skillsString = se::String(L"Skills", menuFont, window.GetWidth()/2+150, continString.GetY()-50, se::Color(0.62f, 0.62f, 0.62f), true);
  quitString1 = se::String(L"Quit", menuFont, window.GetWidth()/2+150, skillsString.GetY()-50, se::Color(0.62f, 0.62f, 0.62f), true);
  experience = se::String(L"", menuFont, window.GetWidth()/2+150, window.GetHeight()-100, se::Color(1.0f, 1.0f, 1.0f), true);
  arrow.SetX(continString.GetX()-arrow.GetWidth());
  arrow.SetY(continString.GetY());
  isInitedGameMenu = true;
  currentSet1 = 0;
}

void DrawGameMenu() {
  static bool pressedUp, pressedDown;
  if (!isInitedGameMenu) {
    InitGameImages();
    pressedUp = pressedDown = false;
  }

  if (input.IsKeyPressed(VK_RETURN)) {
    switch (currentSet1) {
    case 0:
      currentState = ARENA_PLAY;
      break;
    case 1:
      currentState = SKILLS;
      break;
    case 2:
      currentState = QUIT;
      break;
    }
  }
  else {
    int late = currentSet1;
    if (input.IsKeyPressed(VK_DOWN) && !pressedDown) {
      currentSet1 = currentSet1 + 1 <= 2 ? currentSet1 + 1 : currentSet1;
      pressedDown = true;
    }
    else if (input.IsKeyPressed(VK_UP) && !pressedUp) {
      currentSet1 = currentSet1 - 1 >= 0 ? currentSet1 - 1 : currentSet1;
      pressedUp = true;
    }

    if (!input.IsKeyPressed(VK_UP)) pressedUp = false;
    if (!input.IsKeyPressed(VK_DOWN)) pressedDown = false;
    
    switch (late) {
    case 0:
      continString.SetColor(se::Color(0.62f, 0.62f, 0.62f));
      break;
    case 1:
      skillsString.SetColor(se::Color(0.62f, 0.62f, 0.62f));
      break;
    case 2:
      quitString1.SetColor(se::Color(0.62f, 0.62f, 0.62f));
      break;
    }
    switch (currentSet1) {
    case 0:
      arrow.SetY(continString.GetY()-14);
      continString.SetColor(se::Color(1.0f, 1.0f, 1.0f));
      break;
    case 1:
      arrow.SetY(skillsString.GetY()-14);
      skillsString.SetColor(se::Color(1.0f, 1.0f, 1.0f));
      break;
    case 2:
      arrow.SetY(quitString1.GetY()-14);
      quitString1.SetColor(se::Color(1.0f, 1.0f, 1.0f));
      break;
    }
  }

  wchar_t text[50];
  wsprintf(text, L"Experience:%d", player.experience);
  experience.SetText(text);

  window.Clear();

  window.Draw(&backMenu);

  window.Draw(&continString);
  window.Draw(&skillsString);
  window.Draw(&quitString1);

  window.Draw(&arrow);

  window.Draw(&experience);

  window.Display();
}