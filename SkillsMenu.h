#pragma once

#include "GlobalObject.h"

// Card sizes
// width = 200
// height = 300
// skillWidth = 71
// skillHeight = 63
// spheresPosition 

se::Image baseImage;
se::Image skillImage;
se::Sprite baseSprite;
int currentSkill;
se::String name;
se::Sprite skillSprite;
se::Sprite spheresForMenu[3][3];

static bool isInitedSkillsMenu = false;

void InitSkillsMenu() {
  baseImage.LoadFromFile("img\\SkillBack.png");
  baseSprite.SetX(window.GetWidth()/2-100);
  baseSprite.SetY(window.GetHeight()/2-150);
  baseSprite.SetImage(baseImage);
  skillSprite.SetX(baseSprite.GetX()+28);
  skillSprite.SetY(baseSprite.GetY()+baseSprite.GetHeight()-156);
  name.SetX(baseSprite.GetX() + baseSprite.GetWidth()/2 - 45);
  name.SetY(baseSprite.GetY() + baseSprite.GetHeight() - 18);
  name.SetFont(font);
  name.SetText(L"");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      spheresForMenu[i][j].SetImage(sphereImages[i]);
      spheresForMenu[i][j].SetX(baseSprite.GetX()+40*(i+1));
      spheresForMenu[i][j].SetY(baseSprite.GetY()+(80 - j*35));
      spheresForMenu[i][j].SetWidth(30);
      spheresForMenu[i][j].SetHeight(30);
    }
  }
  currentSkill = 0;
  isInitedSkillsMenu = true;
}

void DrawSkills() {
  if (!isInitedSkillsMenu) InitSkillsMenu();

  if (input.IsKeyPressed(VK_ESCAPE)) {
    currentState = GAME_MENU;
    return ;
  }
  
  Skill *skill = skills.second;
  switch (currentSkill) {
  case 0:
    name.SetText(L"Meteorit");
    if (!skillImage.IsValid()) {
      skillImage.LoadFromFile("img\\meteor.png");
      skillSprite.SetImage(skillImage);
      skillSprite.SetWidth(144);
      skillSprite.SetHeight(128);
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          if (skill->impr.k1 <= j && i == 0)
            spheresForMenu[0][j].SetColor(se::Color(0.1f, 0.1f, 0.1f, 1.0f));
          if (skill->impr.k2 <= j && i == 1)
            spheresForMenu[1][j].SetColor(se::Color(0.1f, 0.1f, 0.1f, 1.0f));
          if (skill->impr.k3 <= j && i == 2)
            spheresForMenu[2][j].SetColor(se::Color(0.1f, 0.1f, 0.1f, 1.0f));
        }
      }
    }
    break;
  default:
    break;
  }
  
  window.Clear(se::Color(0.0f, 0.0f, 0.0f));
  window.Draw(&baseSprite);
  window.Draw(&name);
  window.Draw(&skillSprite);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      window.Draw(&spheresForMenu[i][j]);
    }
  }
  window.Display();
}