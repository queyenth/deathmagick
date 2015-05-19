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
  Vertex2D(int x=0, int y=0) : x(x), y(y) {

  }

  friend bool operator==(Vertex2D &left, Vertex2D &right) {
    if (left.x == right.x && left.y == right.y)
      return true;
    else
      return false;
  }

  /// Координата по X
  int x;
  /// Координата по Y
  int y;
};

typedef Vertex2D Point2D;

}
