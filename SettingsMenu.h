#pragma once

#include "GlobalObject.h"
#include "Menu.h"

static se::String resolution, fullscreen, curRes, curFul;
static se::Sprite settingsBox;
static bool isInitedSettingsMenu = false;
static int currentSet2;
static int currentResolution;
static bool fullscreenF;
static std::string resolutions[6] = {"640x480", "800x600", "1024x768", "1280x1024", "1440x900", "1920x1080"};

extern se::Sprite arrow;

void InitSettingsMenu() {
  resolution = se::String("Resolution", menuFont, 100, window.GetHeight()-200, se::Color(), true);
  fullscreen = se::String("Fullscreen", menuFont, 100, window.GetHeight()-230, se::Color(), true);
  curRes = se::String(resolutions[currentResolution], menuFont, resolution.GetX()+250, resolution.GetY(), se::Color(), true);
  curFul = se::String(fullscreenF ? "On" : "Off", menuFont, fullscreen.GetX()+250, fullscreen.GetY(), se::Color(), true);
  settingsBox = se::Sprite(50, 50, window.GetWidth()-100, window.GetHeight()-100, se::Color(0.5f, 0.5f, 0.5f), true);
  arrow.SetX(resolution.GetX()-arrow.GetWidth());
  arrow.SetY(resolution.GetY());
  isInitedSettingsMenu = true;
  currentSet2 = 0;
}

void DrawSettingsMenu() {
  static bool pressedUp, pressedDown, pressedLeft, pressedRight;
  if (!isInitedSettingsMenu) {
    input.UnPressKey(VK_RETURN);
    InitSettingsMenu();
    pressedUp = pressedDown = pressedLeft = pressedRight = false;
  }

  if (input.IsKeyPressed(VK_RETURN)) {
    input.UnPressKey(VK_RETURN);
    window.KillWindow();
    switch (currentResolution) {
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
    window.SetFullscreen(fullscreenF);
    window.CreateUserWindow();
    delete menuFont;
    delete font;
    menuFont = new se::Font(window.GetDC(), L"Arial", 28);
    font = new se::Font(window.GetDC(), L"Arial", 18);
    InitMenuImages();
    InitSettingsMenu();
    FILE *config;
    fopen_s(&config, "config", "w");
    fprintf_s(config, "%d %d", currentResolution, fullscreenF ? 1 : 0);
    fclose(config);
  }
  else if (input.IsKeyPressed(VK_ESCAPE)) {
    currentState = MENU;
    isInitedSettingsMenu = false;
  }
  else if (input.IsKeyPressed(VK_RIGHT) && !pressedRight) {
    switch (currentSet2) {
    case 0:
      currentResolution = currentResolution + 1 <= 5 ? currentResolution + 1 : 0;
      curRes.SetText(resolutions[currentResolution]);
      break;
    case 1:
      fullscreenF = !fullscreenF;
      curFul.SetText(fullscreenF ? "On" : "Off");
      break;
    }
    pressedRight = true;
  }
  else if (input.IsKeyPressed(VK_LEFT) && !pressedLeft) {
    switch (currentSet2) {
    case 0:
      currentResolution = currentResolution - 1 >= 0 ? currentResolution - 1 : 5;
      curRes.SetText(resolutions[currentResolution]);
      break;
    case 1:
      fullscreenF = !fullscreenF;
      curFul.SetText(fullscreenF ? "On" : "Off");
      break;
    }
    pressedLeft = true;
  }
  else {
    if (input.IsKeyPressed(VK_DOWN) && !pressedDown) {
      currentSet2 = currentSet2 + 1 <= 1 ? currentSet2 + 1 : currentSet2;
      pressedDown = true;
    }
    else if (input.IsKeyPressed(VK_UP) && !pressedUp) {
      currentSet2 = currentSet2 - 1 >= 0 ? currentSet2 - 1 : currentSet2;
      pressedUp = true;
    }

    if (!input.IsKeyPressed(VK_UP)) pressedUp = false;
    if (!input.IsKeyPressed(VK_DOWN)) pressedDown = false;
    if (!input.IsKeyPressed(VK_LEFT)) pressedLeft = false;
    if (!input.IsKeyPressed(VK_RIGHT)) pressedRight = false;
    
    switch (currentSet2) {
    case 0:
      arrow.SetY(resolution.GetY());
      break;
    case 1:
      arrow.SetY(fullscreen.GetY());
      break;
    }
  }

  window.Clear();

  window.Draw(&backMenu);
  window.Draw(&settingsBox);
  window.Draw(&resolution);
  window.Draw(&curRes);
  window.Draw(&fullscreen);
  window.Draw(&curFul);
  window.Draw(&arrow);

  window.Display();
}