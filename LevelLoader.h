#pragma once

#include <fstream>
#include <vector>
#include <memory>

#include "GlobalObject.h"

class LevelLoader {
public:
  enum Type { PLAYER, ENEMY, FLOOR };

  LevelLoader() {}
  ~LevelLoader() {}

  void LoadLevel(std::string nameOfLevel, Player &player, std::vector<PhysicsObject *> &floors, std::vector<Enemy> &enemies) {
    se::Image playerImg;
    playerImg.LoadFromFile("img\\player.png");
    player.SetImage(playerImg);
    Enemy enemy(0, 0, 0);
    enemy.SetImage(playerImg);

    nameOfLevel = "lvl\\" + nameOfLevel + ".txt";
    std::ifstream level(nameOfLevel);
    while (!level.eof()) {
      int type;
      int x,y;
      level >> type;
      switch (type) {
      // 0 x y
      case PLAYER:
        level >> x >> y;
        player.SetX(x);
        player.SetY(y);
        break;
      // 1 x y
      case ENEMY:
        level >> x >> y;
        enemy.SetX(x);
        enemy.SetY(y);
        enemies.push_back(Enemy(enemy));
        break;
      // 2 xstart y count
      case FLOOR:
        int count;
        level >> x >> y >> count;
        se::Image image;
        image.LoadFromFile("img\\ground.png");
        for (int i = 0; i < count; i++) {
          Entity entity(x+i*64, y);
          entity.SetImage(image);
          floors.push_back(new Entity(entity));
        }
        break;
      }
    }
    level.close();
  }

private:
};