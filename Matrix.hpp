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
