#pragma once

#include "Renderable.hpp"

#include <Windows.h>
#include <gl/GL.h>
#include <string>

namespace se {

class String : public Renderable {
public:
  String();
  String(std::wstring text, int x = 0, int y = 0, int size = 24,
    int weight = FW_BOLD,
    bool italic = false, bool underline = false,
    bool strikeout = false);
  ~String();

  void SetText(std::wstring);
  std::wstring GetText() const;
  void SetFont(HDC hDC, std::wstring fontName);

  void SetSize(int size);
  void SetWeight(int weight);
  void SetItalic(bool italic);
  void SetUnderline(bool underline);
  void SetStrikeout(bool strikeout);

private:
  void BuildFont(HDC);
  void Render() const;

  std::wstring text;
  GLuint base;

  std::wstring fontName;
  int size;
  int weight;
  bool italic;
  bool underline;
  bool strikeout;
};

}