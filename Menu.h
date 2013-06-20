#pragma once

#include "GlobalObject.h"
#include "Button.h"

se::Image playImage,arenaImage,quitImage,backimage;

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
    if (input.IsLeftMousePressed())
      play.OnClick(NULL);
  }
  else if (arena.OnHover(input.GetMouseX(), input.GetMouseY())) {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    if (input.IsLeftMousePressed())
      arena.OnClick(NULL);
  }
  else if (play.OnHover(input.GetMouseX(), input.GetMouseY())) {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    if (input.IsLeftMousePressed())
      quit.OnClick(NULL);
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