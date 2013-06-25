#pragma once

#include "Window.hpp"
#include "Font.h"
#include "DrawSomeTime.h"
#include "KeySphere.h"
#include "Player.h"
#include "Enemy.h"
#include "Impr.h"

enum GameState { MENU_INIT, MENU, PAUSE, ARENA_INIT, ARENA_DEINIT, ARENA_PLAY, GAME_MENU, SKILLS, QUIT };
GameState currentState = MENU_INIT;

se::Window window(L"Untitled Game", 1024, 768, false);
const se::Input &input = window.GetInput();
se::Camera &camera = window.GetCamera();
se::Font *font;
se::Font *menuFont;
std::vector<tagIMPR> imprs;
se::Sprite backMenu = se::Sprite(0, 0, window.GetWidth(), window.GetHeight());
se::Image backimage;
se::Image sphereImages[3];
std::vector<PhysicsObject *> floors;
Player player;
vector<Enemy> enemies;
std::vector<DrawSomeTime<se::String>> damageString;
std::vector<DrawSomeTime<Entity>> effects;
se::Sprite arrow;
se::Image arrowImg;