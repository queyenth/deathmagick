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
#pragma once

namespace se {

/**
 * @brief Класс, описывающий прямоугольник
 */
class Rect {
public:
  /**
   * @brief Конструктор
   */
  Rect() {
    left = right = top = bottom = 0;
  }

  /**
   * @brief Конструктор, устанавливающий все вершины прямоугольника
   */
  Rect(unsigned int left, unsigned int top, unsigned int right, unsigned int bottom)
    : left(left), right(right), top(top), bottom(bottom) {

  }

  /// Координата левой стороны
  unsigned int left;

  /// Координата правой стороны
  unsigned int right;

  /// Координата верхней стороны
  unsigned int top;

  /// Координата нижней стороны
  unsigned int bottom;
};

}
