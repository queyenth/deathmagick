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

#include "Matrix.hpp"
#include "Color.hpp"
#include "Camera.hpp"
#include "Rect.hpp"

#include <Windows.h>
#include <gl/GL.h>

namespace se {

/**
 * @brief Абстрактный класс объекта, которого можно добавить на экран
 */
class Renderable {
public:
  /**
   * @brief Конструктор
   *
   * @param x : координата по X (по умолчанию 0)
   * @param y : координата по Y (по умолчанию 0)
   */
  Renderable(unsigned int x=0, unsigned int y=0);

  /**
   * @brief Виртуальный деструктор
   */
  virtual ~Renderable();

  /**
   * @brief Функция рисовки
   *
   * Функция устанавливает матрицу, а потом вызывает Render() наследуемого класса
   *
   * @param camera : ссылка на камеру
   */
  void Draw(Camera &) const;

  /**
   * @return координату X
   */
  unsigned int GetX() const;

  /**
   * @return координату Y
   */
  unsigned int GetY() const;

  /**
   * @return ширину объекта
   */
  unsigned int GetWidth() const;

  /**
   * @return высоту объекта
   */
  unsigned int GetHeight() const;

  /**
   * @return цвет объекта
   */
  Color GetColor() const;

  /**
   * @return угол, на который повернут объект
   */
  float GetAngle() const;

  /**
   * @brief Изменяет координату по X
   *
   * @param x : новая координата по X
   */
  void SetX(unsigned int x);

  /**
   * @brief Изменяет координату по Y
   *
   * @param y : новая координата по Y
   */
  void SetY(unsigned int y);

  /**
   * @brief Изменяет цвет объекта
   *
   * @param color : новый цвет
   */
  void SetColor(Color color);

  /**
   * @brief Изменяет ширину объекта
   *
   * @param width : новая ширина
   */
  void SetWidth(unsigned int width);

  /**
   * @brief Изменяет высоту объекта
   *
   * @param height : новая высота
   */
  void SetHeight(unsigned int height);

  /**
   * @brief Перемещает объект на offsetX по X, и на offsetY по Y
   *
   * @param offsetX : смещение по X
   * @param offsetY : смещение по Y
   */
  void Move(unsigned int offsetX, unsigned int offsetY);

  /**
   * @brief Поворачивает объект
   *
   * @param newAngle : угол поворота
   */
  void Rotate(float newAngle);

  /**
   * @brief Изменяет текущий угол поворота
   *
   * @param newAngle : новый угол поворота
   */
   void SetRotate(float newAngle);

  /**
   * @brief Устанавливает флаг flipа объекта по X
   *
   * @param isFlip : флаг flipa
   */
  void FlipX(bool isFlip);

  /**
   * @brief Устанавливает флаг flipа объекта по Y
   *
   * @param isFlip : флаг flipa
   */
  void FlipY(bool isFlip);

protected:
  
  bool isFlippedX;
  bool isFlippedY;

  /// Координаты текстуры
  Rect textureRect;

  /// X координата
  unsigned int x;

  /// Y координата
  unsigned int y;

private:
  /**
   * @brief Метод, который должны реализовать все потомки
   *
   * Отвечает за прорисовку объекта
   */
  virtual void Render() const = 0;

  /**
   * @brief Инициализирует textureRect
   */
  void InitTextureRect();

  /// Ширина объекта
  unsigned int width;

  /// Высота объекта
  unsigned int height;

  /// Цвет объекта
  Color color;

  /// Матрица объекта
  mutable Matrix matrix;

  /// Угол поворота объекта
  float angle;

  mutable bool positionChanged;
};

}
