#pragma once

#include "Window.hpp"
#include "Font.h"
#include "DrawSomeTime.h"
#include "KeySphere.h"
#include "Player.h"
#include "Enemy.h"
#include "Impr.h"

enum GameState {
	MENU_INIT, MENU, SETTINGS, PAUSE, ARENA_INIT, ARENA_DEINIT, ARENA_PLAY, GAME_MENU, SKILLS, QUIT
};
GameState currentState = MENU_INIT;

se::Window window;

se::Input &input = window.GetInput();
se::Camera &camera = window.GetCamera();
se::Font *font;
se::Font *menuFont;
std::vector<tagIMPR> imprs;
se::Sprite backMenu;
se::Image backimage;
se::Image sphereImages[3];
std::vector<PhysicsObject *> floors;
Player player;
std::vector<Enemy> enemies;
std::vector<DrawSomeTime<se::String>> damageString;
std::vector<DrawSomeTime<Entity>> effects;
se::Sprite arrow;
se::Image arrowImg;