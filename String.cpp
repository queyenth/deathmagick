#include "String.hpp"

namespace se {

String::String() {
  base = 0;
  size = 24;
  weight = FW_BOLD;
  italic = underline = strikeout = false;
}

String::String(std::wstring text, int x, int y, int size,
  int weight, bool italic, bool underline, bool strikeout) {
  base = 0;
  this->text = text;
  this->size = size;
  this->weight = weight;
  this->italic = italic;
  this->underline = underline;
  this->strikeout = strikeout;
  this->x = x;
  this->y = y;
}

String::~String() {
  if (base != 0)
    glDeleteLists(base, CountOfCharset);
}

void String::SetText(std::wstring newText) {
  text = newText;
}

std::wstring String::GetText() const {
  return text;
}

void String::Render() const {
  if (base == 0) return;
  glRasterPos2i(x, y);
  glPushAttrib(GL_LIST_BIT);
  glListBase(base - 32);
  glCallLists(text.length()*sizeof(wchar_t), GL_UNSIGNED_BYTE, text.c_str());
  glPopAttrib();
}

void String::BuildFont(HDC hDC) {
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

void String::SetSize(int size) {
  this->size = size;
}

void String::SetWeight(int weight) {
  this->weight = weight;
}

void String::SetItalic(bool italic) {
  this->italic = italic;
}

void String::SetUnderline(bool underline) {
  this->underline = underline;
}

void String::SetStrikeout(bool strikeout) {
  this->strikeout = strikeout;
}

void String::SetFont(HDC hDC, std::wstring fontName) {
  this->fontName = fontName;
  BuildFont(hDC);
}

void String::SetX(int x) {
  this->x = x;
}

void String::SetY(int y) {
  this->y = y;
}

}