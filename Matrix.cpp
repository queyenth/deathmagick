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
#include "Matrix.hpp"

namespace se {

/**
 * @brief Конструктор, принимающий значения всех клеток матрицы
 */
Matrix::Matrix(float m0, float m1, float m2, float m3,
               float m4, float m5, float m6, float m7,
               float m8, float m9, float m10, float m11,
               float m12, float m13, float m14, float m15) {
  matrix[0] = m0; matrix[1] = m1; matrix[2] = m2; matrix[3] = m3;
  matrix[4] = m4; matrix[5] = m5; matrix[6] = m6; matrix[7] = m7;
  matrix[8] = m8; matrix[9] = m9; matrix[10] = m10; matrix[11] = m11;
  matrix[12] = m12; matrix[13] = m13; matrix[14] = m14; matrix[15] = m15;
}

/**
 * @brief Конструктор, устанавливающий матрицу как единичную
 */
Matrix::Matrix() {
  // Устанавливаем матрицу как единичную
    matrix[0] = 1.0f;  matrix[1] = 0.0f;  matrix[2] = 0.0f;  matrix[3] = 0.0f;
    matrix[4] = 0.0f;  matrix[5] = 1.0f;  matrix[6] = 0.0f;  matrix[7] = 0.0f;
    matrix[8] = 0.0f;  matrix[9] = 0.0f; matrix[10] = 1.0f; matrix[11] = 0.0f;
   matrix[12] = 0.0f; matrix[13] = 0.0f; matrix[14] = 0.0f; matrix[15] = 1.0f;
}

/**
 * @brief Изменяет элемент матрицы
 *
 * @param position : позиция в матрице
 * @param value : новое значение
 */
void Matrix::Set(int position, float value) {
  matrix[position] = value;
}

/**
 * @param position : позиция в матрице
 * @return значение в заданной позиции
 */
float Matrix::Get(int position) const {
  return matrix[position];
}

/**
 * @return всю матрицу
 */
const float *Matrix::GetMatrix() const {
  return matrix;
}

}
