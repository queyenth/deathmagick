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
 * @brief Класс описывает точку на экране
 */
class Vertex2D {
public:
  /**
   * @brief Конструктор
   *
   * @param x : координата по X (по умолчанию 0)
   * @param y : координата по Y (по умолчанию 0)
   */
  Vertex2D(float x=0, float y=0) : x(x), y(y) {

  }

  friend bool operator==(Vertex2D left, Vertex2D right) {
    if (left.x == right.x && left.y == right.y)
      return true;
    else
      return false;
  }

  /// Координата по X
  float x;
  /// Координата по Y
  float y;
};

typedef Vertex2D Point2D;

}
