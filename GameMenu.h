#pragma once

#include "GlobalObject.h"

static se::String continString,skillsString,returnToMenu,quitString1;
static se::String experience;
static bool isInitedGameMenu = false;
static int currentSet1;
extern se::Sprite backMenu;

void InitGameImages() {
  continString = se::String("Continue", menuFont, window.GetWidth()/2+150, window.GetHeight() - window.GetHeight()/3, se::Color(), true);
  skillsString = se::String("Skills", menuFont, window.GetWidth()/2+150, continString.GetY()-50, se::Color(), true);
  returnToMenu = se::String("Return to menu", menuFont, window.GetWidth()/2+150, skillsString.GetY()-50, se::Color(), true);
  quitString1 = se::String("Quit", menuFont, window.GetWidth()/2+150, returnToMenu.GetY()-50, se::Color(), true);
  experience = se::String("", menuFont, window.GetWidth()/2+150, window.GetHeight()-100, se::Color(), true);
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

  arrow.SetX(window.GetWidth()/2+150-arrow.GetWidth()/2);
  if (input.IsKeyPressed(VK_RETURN)) {
    switch (currentSet1) {
    case 0:
      currentState = ARENA_PLAY;
      break;
    case 1:
      currentState = SKILLS;
      break;
    case 2:
      currentState = ARENA_DEINIT;
      break;
    case 3:
      currentState = QUIT;
      break;
    }
    input.UnPressKey(VK_RETURN);
  }
  else {
    if (input.IsKeyPressed(VK_DOWN) && !pressedDown) {
      currentSet1 = currentSet1 + 1 <= 3 ? currentSet1 + 1 : currentSet1;
      pressedDown = true;
    }
    else if (input.IsKeyPressed(VK_UP) && !pressedUp) {
      currentSet1 = currentSet1 - 1 >= 0 ? currentSet1 - 1 : currentSet1;
      pressedUp = true;
    }

    if (!input.IsKeyPressed(VK_UP)) pressedUp = false;
    if (!input.IsKeyPressed(VK_DOWN)) pressedDown = false;

    int x = window.GetWidth()/2+150;
    continString.SetX(x);
    skillsString.SetX(x);
    returnToMenu.SetX(x);
    quitString1.SetX(x);

    x += arrow.GetWidth()/2;
    switch (currentSet1) {
    case 0:
      arrow.SetY(continString.GetY());
      continString.SetX(x);
      break;
    case 1:
      arrow.SetY(skillsString.GetY());
      skillsString.SetX(x);
      break;
    case 2:
      arrow.SetY(returnToMenu.GetY());
      returnToMenu.SetX(x);
      break;
    case 3:
      arrow.SetY(quitString1.GetY());
      quitString1.SetX(x);
      break;
    }
  }

  char text[50];
  sprintf_s(text, 50, "Experience: %d", player.experience);
  experience.SetText(text);

  window.Clear();

  window.Draw(&backMenu);

  window.Draw(&continString);
  window.Draw(&skillsString);
  window.Draw(&returnToMenu);
  window.Draw(&quitString1);

  window.Draw(&arrow);

  window.Draw(&experience);

  window.Display();
}