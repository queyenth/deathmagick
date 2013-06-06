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
 * @brief Класс, представляющий матрицу 4x4
 */
class Matrix {
public:
  /**
   * @brief Конструктор, устанавливающий матрицу как единичную
   */
  Matrix();

  /**
   * @brief Конструктор, принимающий значения всех клеток матрицы
   */
  Matrix(float m0, float m1, float m2, float m3,
         float m4, float m5, float m6, float m7,
         float m8, float m9, float m10, float m11,
         float m12, float m13, float m14, float m15);

  /**
   * @brief Изменяет элемент матрицы
   *
   * @param position : позиция в матрице
   * @param value : новое значение
   */
  void Set(int position, float value);

  /**
   * @param position : позиция в матрице
   * @return значение в заданной позиции
   */
  float Get(int position) const;

  /**
   * @return всю матрицу
   */
  const float *GetMatrix() const;
private:

  /// Массив, хранящий всю матрицу
  float matrix[16];
};

}
