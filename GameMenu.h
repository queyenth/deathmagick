#pragma once

#include "GlobalObject.h"

static se::Image continImage,skillsImage;
static se::String experience = se::String(L"", font, 450, 300, se::Color(), true);
static bool isInitedGameMenu = false;

void InitGameImages() {
  continImage.LoadFromFile("img\\contin.png");
  skillsImage.LoadFromFile("img\\skills.png");
  experience.SetFont(font);
  isInitedGameMenu = true;
}

void DrawGameMenu() {
  if (!isInitedGameMenu) {
    InitGameImages();
  }
  static Button contin = Button(continImage, ContinuePressed, window.GetWidth()/4, window.GetHeight()/2+75, 200, 50, se::Color());
  static Button skillsB = Button(skillsImage, SkillsPressed, window.GetWidth()/4, window.GetHeight()/2-25, 200, 50, se::Color());
  static Button quit = Button(quitImage, QuitPressed, window.GetWidth()/4, window.GetHeight()/2-125, 200, 50, se::Color());
  if (quit.OnHover(input.GetMouseX(), input.GetMouseY())) {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    if (input.IsLeftMousePressed())
      contin.OnClick(NULL);
  }
  else if (skillsB.OnHover(input.GetMouseX(), input.GetMouseY())) {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    skillsB.Move(-1, -3);
    if (input.IsLeftMousePressed())
      skillsB.OnClick(NULL);
    skillsB.Move(1, 3);
  }
  else if (quit.OnHover(input.GetMouseX(), input.GetMouseY())) {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    if (input.IsLeftMousePressed())
      quit.OnClick(NULL);
  }
  else {
    SetCursor(LoadCursor(NULL, IDC_ARROW));
  }

  wchar_t text[50];
  wsprintf(text, L"Experience:%d", player.experience);
  experience.SetText(text);

  window.Clear();

  window.Draw(&backMenu);

  window.Draw(&contin);
  window.Draw(&skillsB);
  window.Draw(&quit);

  window.Draw(&experience);

  window.Display();
}