#pragma once

#include "Window.hpp"
#include "Font.h"
#include "DrawSomeTime.h"
#include "KeySphere.h"
#include "Player.h"
#include "Enemy.h"
#include "Impr.h"

se::Window window(L"Untitled Game", 640, 480, false);
const se::Input &input = window.GetInput();
se::Camera &camera = window.GetCamera();
se::Font *font;
std::vector<tagIMPR> imprs;
se::Sprite backMenu = se::Sprite(0, 0, window.GetWidth(), window.GetHeight());
se::Image sphereImages[3];
std::vector<PhysicsObject *> floors;
Player player;
vector<Enemy> enemies;
std::vector<DrawSomeTime<se::String>> damageString;
std::vector<DrawSomeTime<Entity>> effects;

enum GameState { MENU_INIT, MENU, PAUSE, ARENA_INIT, ARENA_DEINIT, ARENA_PLAY, GAME_MENU, SKILLS, QUIT };

GameState currentState = MENU_INIT;

void PlayPressed(void *data) {
  currentState = MENU;
}

void ArenaPressed(void *data) {
  currentState = ARENA_INIT;
}

void QuitPressed(void *data) {
  currentState = QUIT;
}

void ContinuePressed(void *data) {
  currentState = ARENA_PLAY;
}

void SkillsPressed(void *data) {
  currentState = SKILLS;
}