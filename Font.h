#pragma once

#include <string>
#include <Windows.h>
#include <gl/GL.h>

namespace se {
class Font {
public:
  enum { CountOfCharset = 96 };
  Font() {
    base = 0;
    size = 24;
    weight = FW_BOLD;
    italic = underline = strikeout = false;
  }

  Font(HDC hDC, std::wstring fontName, int size = 24,
    int weight = FW_BOLD,
    bool italic = false, bool underline = false,
    bool strikeout = false) {
    base = 0;
    this->size = size;
    this->weight = weight;
    this->italic = italic;
    this->underline = underline;
    this->strikeout = strikeout;
    this->fontName = fontName;
    BuildFont(hDC);
  }

  ~Font() {
    glDeleteLists(base, CountOfCharset);
  }

  void BuildFont(HDC hDC) {
    HFONT font;
    HFONT oldfont;
    base = glGenLists(CountOfCharset);
    font = CreateFont(-size, 0, 0, 0, weight, italic, underline, strikeout,
      ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
      FF_DONTCARE | DEFAULT_PITCH, fontName.c_str());
    oldfont = (HFONT)SelectObject(hDC, font);
    wglUseFontBitmaps(hDC, 32, CountOfCharset, base);
    SelectObject(hDC, oldfont);
    DeleteObject(font);
}

  void SetSize(int size) {
    this->size = size;
  }

  void SetWeight(int weight) {
    this->weight = weight;
  }

  void SetItalic(bool italic) {
    this->italic = italic;
  }

  void SetUnderline(bool underline) {
    this->underline = underline;
  }

  void SetStrikeout(bool strikeout) {
    this->strikeout = strikeout;
  }

  void SetFont(HDC hDC, std::wstring fontName) {
    this->fontName = fontName;
    BuildFont(hDC);
  }

  GLuint base;
  std::wstring fontName;
  int size;
  int weight;
  bool italic;
  bool underline;
  bool strikeout;
};

}