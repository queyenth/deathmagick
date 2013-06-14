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

#include "Renderable.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include "Rect.hpp"

namespace se {

/**
 * @brief Класс реализует объект на экране, который может быть перемещен и т.д.
 */
class Sprite : public Renderable {
public:
  /**
   * @brief Конструктор
   *
   * @param x : координата по X(по умолчанию 0)
   * @param y : координата по Y(по умолчанию 0)
   */
  Sprite(unsigned int x=0, unsigned int y=0, unsigned int width=0, unsigned int height=0, Color color = Color(), bool isFixed=false);

  /**
   * @brief Виртуальный деструктор
   */
  virtual ~Sprite();

  /**
   * @brief Устанавливает новое изображение спрайта
   *
   * @param image : изображение спрайта
   */
  void SetImage(Image &image);

protected:
  Image image;

private:
  /**
   * @brief Смотри Renderable::Render()
   *
   * Рисует спрайт с наложенным изображением
   */
  void Render() const;

  /// Текущий угол поворота
  double angle;
};

}
