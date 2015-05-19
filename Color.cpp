#include "Color.hpp"

namespace se {

const Color White(1, 1, 1);
const Color Black(0, 0, 0);
const Color Red(1, 0, 0);
const Color Green(0, 1, 0);
const Color Blue(0, 0, 1);

/**
 * @brief Конструктор
 *
 * @param r : красный цвет (по умолчанию 1.0)
 * @param g : зеленый цвет (по умолчанию 1.0)
 * @param b : синий цвет (по умолчанию 1.0)
 */
Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) { }

/**
 * @return Значение красного цвета
 */
float Color::GetRed() const {
  return r;
}

/**
 * @return Значение зеленого цвета
 */
float Color::GetGreen() const {
  return g;
}

/**
 * @return Значение синего цвета
 */
float Color::GetBlue() const {
  return b;
}

float Color::GetAlpha() const {
  return a;
}

/**
 * @brief Устанавливает новое значение красного цвета
 *
 * @param r : значение красного цвета
 */
void Color::SetRed(float r) {
  this->r = r;
}

/**
 * @brief Устанавливает новое значение зеленого цвета
 *
 * @param g : значение зеленого цвета
 */
void Color::SetGreen(float g) {
  this->g = g;
}

/**
 * @brief Устанавливает новое значение синего цвета
 *
 * @param b : значение синего цвета
 */
void Color::SetBlue(float b) {
  this->b = b;
}

void Color::SetAlpha(float a) {
  this->a = a;
}

}
