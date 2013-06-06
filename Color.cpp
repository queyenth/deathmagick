/**
 * SimpleEngine.
 * Copyright (C) 2013 oveRan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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
Color::Color(float r, float g, float b) : r(r), g(g), b(b) { }

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

}
