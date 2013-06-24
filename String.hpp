#pragma once

#include "Renderable.hpp"
#include "Font.h"

#include <string>

namespace se {

class String : public Renderable {
public:

  String();
  String(std::wstring text, Font *font, int x = 0, int y = 0, Color color = Color(1.0f, 1.0f, 1.0f), bool fixed = true);
  ~String();

  void SetText(std::wstring);
  std::wstring GetText() const;
  void SetFont(Font *font);
private:

  void Render() const;

  std::wstring text;
  Font *font;
};

}