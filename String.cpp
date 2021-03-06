#include "String.hpp"

namespace se {

String::String() : se::Renderable(0, 0, 0, 0, se::Color(), true) {

}

String::String(std::string text, Font *font, int x, int y, Color color, bool fixed) : se::Renderable(x, y, 0, 0, color, fixed) {
  this->text = text;
  this->font = font;
}

String::~String() {

}

void String::SetText(std::string newText) {
  text = newText;
}

std::string String::GetText() const {
  return text;
}

void String::Render() const {
  if (font->base == 0) return;
  glRasterPos2i(0, 0);
  glListBase(font->base);
  glCallLists(text.length(), GL_UNSIGNED_BYTE, text.c_str());
}

void String::SetFont(Font *font) {
  this->font = font;
}

}