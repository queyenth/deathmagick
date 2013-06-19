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
#include "Renderable.hpp"

#include <iostream>
#include <cmath>

using namespace std;

namespace se {

/**
 * @brief Конструктор
 *
 * @param x : координата по X (по умолчанию 0)
 * @param y : координата по Y (по умолчанию 0)
 */
Renderable::Renderable(unsigned int x, unsigned int y, unsigned int width, unsigned int height, Color color, bool isFixed) : x(x), y(y), width(width), height(height), angle(0), positionChanged(true),
isFlippedX(false), isFlippedY(false), isFixed(isFixed), color(color) {
  InitTextureRect();
}

/**
 * @brief Виртуальный деструктор
 */
Renderable::~Renderable() {
  // Nothing to do
}

/**
 * @brief Перемещает объект на offsetX по X, и на offsetY по Y
 *
 * @param offsetX : смещение по X
 * @param offsetY : смещение по Y
 */
void Renderable::Move(int offsetX, int offsetY) {
  SetX(x + offsetX);
  SetY(y + offsetY);
}

/**
 * @brief Изменяет координату по X
 *
 * @param x : новая координата по X
 */
void Renderable::SetX(unsigned int x) {
  this->x = x;
  positionChanged = true;
}

/**
 * @brief Изменяет координату по Y
 *
 * @param y : новая координата по Y
 */
void Renderable::SetY(unsigned int y) {
  this->y = y;
  positionChanged = true;
}

/**
 * @brief Изменяет ширину объекта
 *
 * @param width : новая ширина
 */
void Renderable::SetWidth(unsigned int width) {
  this->width = width;
}

/**
 * @brief Изменяет высоту объекта
 *
 * @param height : новая высота
 */
void Renderable::SetHeight(unsigned int height) {
  this->height = height;
}

/**
 * @brief Изменяет цвет объекта
 *
 * @param color : новый цвет
 */
void Renderable::SetColor(Color color) {
  this->color = color;
}

void Renderable::SetFixedMode(bool isFixed) {
  this->isFixed = isFixed;
}

/**
 * @return координату X
 */
unsigned int Renderable::GetX() const {
  return x;
}

/**
 * @return координату Y
 */
unsigned int Renderable::GetY() const {
  return y;
}

/**
 * @return ширину объекта
 */
unsigned int Renderable::GetWidth() const {
  return width;
}

/**
 * @return высоту объекта
 */
unsigned int Renderable::GetHeight() const {
  return height;
}

/**
 * @return цвет объекта
 */
Color Renderable::GetColor() const {
  return color;
}

/**
 * @return угол, на который повернут объект
 */
float Renderable::GetAngle() const {
  return angle;
}

bool Renderable::IsFixed() const {
  return isFixed;
}

/**
 * @brief Функция рисовки
 *
 * Функция устанавливает матрицу, а потом вызывает Render() наследуемого класса
 *
 * @param camera : ссылка на камеру
 */
void Renderable::Draw(Camera &camera) const {
  // Переходим к матрице модели
  glMatrixMode(GL_MODELVIEW);

  // Сохраняем предыдущую матрицу
  glPushMatrix();

  // Если положение объекта изменилось, или изменилась камера, МОДИФИЦИРУЕМ МАТРИЦУ FUCK YEAH
  if (camera.Changed() || positionChanged) {
    int newX = isFixed ? x : x - camera.GetViewX();
    int newY = isFixed ? y : y - camera.GetViewY();
    matrix.Set(12, newX);
    matrix.Set(13, newY);
    positionChanged = false;
  }

  // Перемножаем текущую матрицу с матрицей рисуемого объекта
  glMultMatrixf(matrix.GetMatrix());

  // Устанавливаем цвет
  if (color.GetAlpha() != 0.0f) {
    glColor4f(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
  }
  else
    glColor3f(color.GetRed(), color.GetGreen(), color.GetBlue());

  // Даем наследуемому классу рисовать что он там хочет
  Render();

  // Возвращаемся к матрице модели (мало ли что наследуемый класс наделал)
  glMatrixMode(GL_MODELVIEW);

  // Возвращаем сохраненную матрицу
  glPopMatrix();
}

/**
 * @brief Поворачивает объект
 *
 * @param newAngle : угол поворота
 */
void Renderable::Rotate(float newAngle) {

  angle += newAngle;
  angle = fmod(angle, 360);
  while (angle < 0) angle += 360;

  // Сразу вычисляем косинус и синус, ибо дорогостоящая операция
  float Cos = cosf(angle*(float)(3.14159265/180));
  float Sin = sinf(angle*(float)(3.14159265/180));

  // Обновляем матрицу
  matrix.Set(0, Cos);
  matrix.Set(1, Sin);
  matrix.Set(4, -Sin);
  matrix.Set(5, Cos);

}
/**
 * @brief Изменяет текущий угол поворота
 *
 * @param newAngle : новый угол поворота
 */
void Renderable::SetRotate(float newAngle) {
  angle = newAngle;
  Rotate(0);
}

/**
 * @brief Устанавливает флаг flipа объекта по X
 *
 * @param isFlip : флаг flipa
 */
void Renderable::FlipX(bool isFlip) {
  isFlippedX = isFlip;
}

/**
 * @brief Устанавливает флаг flipа объекта по Y
 *
 * @param isFlip : флаг flipa
 */
void Renderable::FlipY(bool isFlip) {
  isFlippedY = isFlip;
}

bool Renderable::IsFlippedX() const {
  return isFlippedX;
}

bool Renderable::IsFlippedY() const {
  return isFlippedY;
}

void Renderable::InitTextureRect() {
  textureRect.left = textureRect.top = 0.0f;
  textureRect.right = textureRect.bottom = 1.0f;
}

}
