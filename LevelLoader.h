#pragma once

#include <fstream>
#include <vector>
#include <memory>

#include "Player.h"
#include "Enemy.h"
#include "Image.hpp"

extern Player player;
extern std::vector<Enemy> enemies;
extern std::vector<PhysicsObject *> floors;

class LevelLoader {
public:
  enum Type { PLAYER, ENEMY, FLOOR, STAIR, RUNE, TABLE };

  LevelLoader() {}
  ~LevelLoader() {}

  void LoadLevel(std::string nameOfLevel) {
    se::Image playerImg;
    playerImg.LoadFromFile("img\\player.png");
    player.SetImage(playerImg);
    Enemy enemy(0, 0);
    enemy.SetImage(playerImg);

    runeImg.LoadFromFile("img\\rune.png");
    se::Sprite rune(0, 0);
    rune.SetImage(runeImg);

    nameOfLevel = "lvl\\" + nameOfLevel + ".txt";
    std::ifstream level(nameOfLevel);
    while (!level.eof()) {
      int type, count;
      int x,y;
      level >> type;
      se::Image image;
      switch (type) {
      // 1 type x y
      case ENEMY:
        level >> type >> x >> y;
        enemy.SetX(x);
        enemy.SetY(y);
        enemies.push_back(Enemy(enemy));
        break;
      // 2 type xstart y count
      case FLOOR:
        level >> type >> x >> y >> count;
        if (type == 1)
          image.LoadFromFile("img\\ground.png");
        else if (type == 2)
          image.LoadFromFile("img\\ground_down.png");
        for (int i = 0; i < count; i++) {
          Entity entity(x+i*64, y);
          entity.SetImage(image);
          floors.push_back(new Entity(entity));
        }
        break;
      // 0 x y
      case PLAYER:
        level >> x >> y;
        player.SetX(x);
        player.SetY(y);
        break;
      // 3 x ystart count
      case STAIR:
        level >> x >> y >> count;
        stairs.push_back(Stair(count, x, y));
        break;
      // 4 x y
      case RUNE:
        level >> x >> y;
        rune.SetX(x);
        rune.SetY(y);
        runes.push_back(se::Sprite(rune));
        break;
      // 5 x y text
      case TABLE:
        // TODO: Do table;
        std::string text;
        level >> x >> y >> text;
        break;
      }
    }
    level.close();
  }

private:
};