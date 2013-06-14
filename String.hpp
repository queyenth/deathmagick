#pragma once

#include "Renderable.hpp"
#include "Font.h"

#include <string>

namespace se {

class String : public Renderable {
public:

  String();
  String(std::wstring text, Font *font, int x = 0, int y = 0, int size = 24,
    int weight = FW_BOLD,
    bool italic = false, bool underline = false,
    bool strikeout = false);
  ~String();

  void SetText(std::wstring);
  std::wstring GetText() const;
  void SetFont(Font *font);
private:

  void Render() const;

  std::wstring text;
  std::wstring fontName;
  Font *font;
};

}