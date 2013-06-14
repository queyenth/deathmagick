#include "String.hpp"

namespace se {

String::String() : se::Renderable(0, 0, 0, 0, se::Color(), true) {

}

String::String(std::wstring text, Font *font, int x, int y, int size,
  int weight, bool italic, bool underline, bool strikeout) : se::Renderable(x, y, 0, 0, se::Color(), true) {
  this->text = text;
  this->font = font;
}

String::~String() {

}

void String::SetText(std::wstring newText) {
  text = newText;
}

std::wstring String::GetText() const {
  return text;
}

void String::Render() const {
  if (font->base == 0) return;
  glRasterPos2i(0, 0);
  glPushAttrib(GL_LIST_BIT);
  glListBase(font->base - 32);
  glCallLists(text.length()*sizeof(wchar_t), GL_UNSIGNED_BYTE, text.c_str());
  glPopAttrib();
}

void String::SetFont(Font *font) {
  this->font = font;
}

}