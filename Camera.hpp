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
  Camera(float x, float y) : viewPoint(x, y), isChanged(true) {
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
  void SetViewX(float x) {
    viewPoint.x = x;
    isChanged = true;
  }

  /**
   * @brief Изменяет точку просмотра камеры по Y.
   *
   * @param y : новая точка камеры по Y
   */
  void SetViewY(float y) {
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
  void OffsetViewByX(float x) {
    viewPoint.x += x;
    isChanged = true;
  }

  /**
   * @brief Перемещает точку просмотра камеры на x пикселей по Y.
   *
   * @param y : offset параметр
   */
  void OffsetViewByY(float y) {
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
  float GetViewX() const {
    return viewPoint.x;
  }

  /**
   * @return точку просмотра камеры по Y
   */
  float GetViewY() const {
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
