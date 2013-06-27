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
se::Image descImg;
se::Sprite desc;
std::string nameOfSkill;

void InitSkillsMenu() {
  baseImage.LoadFromFile("img\\SkillBack.png");
  baseSprite.SetX(window.GetWidth()/2-100);
  baseSprite.SetY(window.GetHeight()/2-150);
  baseSprite.SetImage(baseImage);
  baseSprite.SetFixedMode(true);
  skillSprite.SetX(baseSprite.GetX()+28);
  skillSprite.SetY(baseSprite.GetY()+baseSprite.GetHeight()-156);
  skillSprite.SetFixedMode(true);
  name.SetX(baseSprite.GetX() + baseSprite.GetWidth()/2 - 45);
  name.SetY(baseSprite.GetY() + baseSprite.GetHeight() - 18);
  name.SetFont(font);
  name.SetFixedMode(true);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      spheresForMenu[i][j].SetImage(sphereImages[i]);
      spheresForMenu[i][j].SetX(baseSprite.GetX()+40*(i+1));
      spheresForMenu[i][j].SetY(baseSprite.GetY()+(80 - j*35));
      spheresForMenu[i][j].SetWidth(30);
      spheresForMenu[i][j].SetHeight(30);
      spheresForMenu[i][j].SetFixedMode(true);
    }
  }
  currentSkill = 0;
  ShowCursor(TRUE);
}

void DrawSkills() {
  if (input.IsKeyPressed(VK_ESCAPE)) {
    currentState = GAME_MENU;
    return ;
  }
  
  Skill *skill;
  switch (currentSkill) {
  case 0:
    skill = SkillFactory::MakeSkill(KeySphere(2, 1, 0), imprs[currentSkill]).get();
    nameOfSkill = "Meteorit";
    name.SetText(std::wstring(nameOfSkill.begin(), nameOfSkill.end()));
    if (!skillImage.IsValid()) {
      skillImage.LoadFromFile("img\\meteor.png");
      skillSprite.SetImage(skillImage);
      skillSprite.SetWidth(144);
      skillSprite.SetHeight(128);
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          if (imprs[currentSkill].k1 <= j && i == 0)
            spheresForMenu[0][j].SetColor(se::Color(0.1f, 0.1f, 0.1f, 1.0f));
          if (imprs[currentSkill].k2 <= j && i == 1)
            spheresForMenu[1][j].SetColor(se::Color(0.1f, 0.1f, 0.1f, 1.0f));
          if (imprs[currentSkill].k3 <= j && i == 2)
            spheresForMenu[2][j].SetColor(se::Color(0.1f, 0.1f, 0.1f, 1.0f));
        }
      }
    }
    break;
  default:
    break;
  }
  
  int mx,my;
  mx = input.GetMouseX();
  my = window.GetHeight() - input.GetMouseY();

  window.Clear(se::Color(0.5f, 0.5f, 0.5f));
  window.Draw(&baseSprite);
  window.Draw(&name);
  window.Draw(&skillSprite);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      se::Sprite *sphere = &spheresForMenu[i][j];
      window.Draw(sphere);
    }
  }
  char lolka[5];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      se::Sprite *sphere = &spheresForMenu[i][j];
       // If mouse on hover on sphere, render the description
      if ((sphere->GetX() <= mx && mx <= sphere->GetX()+sphere->GetWidth()) &&
        (sphere->GetY() <= my && my <= sphere->GetY()+sphere->GetHeight())) {
          sprintf(lolka, "%d_%d", i, j);
          std::string nameOfFile = "img\\" + nameOfSkill + (std::string)lolka + ".png";
          descImg.LoadFromFile(nameOfFile);
          desc = se::Sprite(sphere->GetX(), sphere->GetY()-descImg.GetHeight(), 0, 0, se::Color(), true);
          desc.SetImage(descImg);
          window.Draw(&desc);
      }
    }
  }

  window.Display();
}