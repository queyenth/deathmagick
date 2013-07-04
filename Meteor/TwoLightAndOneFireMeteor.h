#pragma once

#include "OneFireMeteor.h"
#include "OneLightMeteor.h"

class TwoLightAndOneFireMeteor : public Meteor {
public:
  OneFireMeteor fire[3];
  
  TwoLightAndOneFireMeteor() {
    countOfMeteors = 0;
    lastMeteor = 0;
    waitingNew = true;
    allDone[0] = allDone[1] = allDone[2] = true;
  }

  virtual bool operation() override {
    // Если с момента падения последнего метеорита прошло полсекунды, и нужен новый метеорит
    if (waitingNew && GetTickCount() - lastMeteor > 500 && countOfMeteors < 3) {
      fire[countOfMeteors].Cast(player);
      fire[countOfMeteors].speed = 8;
      countOfMeteors++;
      waitingNew = false;
    }
    // Перебираем все метеориты
    for (int i = 0; i < countOfMeteors; i++) {
      // Если метеорит еще не упал
      if (!fire[i].FireTime) {
        // пускаем его
        fire[i].operation();
        if (fire[i].FireTime) {
          waitingNew = true;
          lastMeteor = GetTickCount();
          OneLightMeteor *meteor = new OneLightMeteor();
          meteor->base = fire[i].base;
          meteor->operation();
          delete meteor;
        }
      }
      else if (allDone[i]) {
        allDone[i] = fire[i].operation();
      }
    }
    return allDone[0] || allDone[1] || allDone[2];
  }

  int countOfMeteors;
  DWORD lastMeteor;
  bool waitingNew;
  bool allDone[3];
};