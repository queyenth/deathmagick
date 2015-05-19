#pragma once

#include "Vertex2D.hpp"

namespace se {

class Camera {
public:

  /**
   * @brief Конструктор по умолчанию
   */
  Camera() : viewPoint(0, 0), isChanged(true) {
    // Nothing to do
  }

  /**
   * @brief Конструктор, берущий для камеры другую точку
   *
   * @param point : точка просмотра
   */
  Camera(Vertex2D point) : viewPoint(point), isChanged(true) {
    // Nothing to do
  }

  /**
   * @brief Конструктор, берущий для камеры две точки
   *
   * @param x : точка просмотра по X
   * @param y : точка просмотра по Y
   */
  Camera(int x, int y) : viewPoint(x, y), isChanged(true) {
    // Nothing to do
  }

  /**
   * @brief Деструктор
   */
  ~Camera() {
    // Nothing to do
  }

  /**
   * @brief Устанавливает точку просмотра камеры.
   *
   * @param point : новая точка камеры
   */
  void SetViewPoint(Vertex2D point) {
    SetViewX(point.x);
    SetViewY(point.y);
  }

  /**
   * @brief Изменяет точку просмотра камеры по X.
   *
   * @param x : новая точка камеры по X
   */
  void SetViewX(int x) {
    viewPoint.x = x;
    isChanged = true;
  }

  /**
   * @brief Изменяет точку просмотра камеры по Y.
   *
   * @param y : новая точка камеры по Y
   */
  void SetViewY(int y) {
    viewPoint.y = y;
    isChanged = true;
  }

  /**
   * @brief Перемещает точку просмотра камеры на offsetPoint.
   *
   * @param offsetPoint : вектор перемещения
   */
  void OffsetViewByPoint(Vertex2D offsetPoint) {
    OffsetViewByX(offsetPoint.x);
    OffsetViewByY(offsetPoint.y);
  }

  /**
   * @brief Перемещает точку просмотра камеры на x пикселей по X.
   *
   * @param x : offset параметр
   */
  void OffsetViewByX(int x) {
    viewPoint.x += x;
    isChanged = true;
  }

  /**
   * @brief Перемещает точку просмотра камеры на x пикселей по Y.
   *
   * @param y : offset параметр
   */
  void OffsetViewByY(int y) {
    viewPoint.y += y;
    isChanged = true;
  }

  /**
   * @return точку просмотра камеры
   */
  Vertex2D GetViewPoint() const {
    return viewPoint;
  }

  /**
   * @return точку просмотра камеры по X
   */
  int GetViewX() const {
    return viewPoint.x;
  }

  /**
   * @return точку просмотра камеры по Y
   */
  int GetViewY() const {
    return viewPoint.y;
  }

  /**
   * @brief Изменилась ли камера?
   */
  bool Changed() const {
    return isChanged;
  }

  /**
   * @brief Изменяет состояние камеры
   *
   * @param changed : новое состояние
   */
  void SetChanged(bool changed) {
    isChanged = changed;
  }
private:
  /// Точка просмотра камеры
  Vertex2D viewPoint;

  /// Флаг, изменилась ли камера
  bool isChanged;
};

}
