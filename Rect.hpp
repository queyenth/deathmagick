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
    left = right = top = bottom = 0.0f;
  }

  /**
   * @brief Конструктор, устанавливающий все вершины прямоугольника
   */
  Rect(float left, float top, float right, float bottom)
    : left(left), right(right), top(top), bottom(bottom) {

  }

  /// Координата левой стороны
  float left;

  /// Координата правой стороны
  float right;

  /// Координата верхней стороны
  float top;

  /// Координата нижней стороны
  float bottom;
};

}
