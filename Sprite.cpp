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
#include "Sprite.hpp"
#include <iostream>

namespace se {

/**
 * @brief Конструктор
 *
 * @param x : координата по X(по умолчанию 0)
 * @param y : координата по Y(по умолчанию 0)
 */
Sprite::Sprite(unsigned int x, unsigned int y) : Renderable(x, y), image() {

}

/**
 * @brief Виртуальный деструктор
 */
Sprite::~Sprite() {
  // Nothing to do
}

/**
 * @brief Устанавливает новое изображение спрайта
 *
 * @param image : изображение спрайта
 */
void Sprite::SetImage(Image &image) {
  this->image = image;
  SetWidth(image.GetWidth());
  SetHeight(image.GetHeight());
}

/**
 * @brief Смотри Renderable::Render()
 *
 * Рисует спрайт с наложенным изображением
 */
void Sprite::Render() const {

  // Запоминаем высоту и ширину спрайта
  float width = GetWidth();
  float height = GetHeight();

  float top = isFlippedY ? textureRect.bottom : textureRect.top;
  float left = isFlippedX ? textureRect.right : textureRect.left;
  float right = isFlippedX ? textureRect.left : textureRect.right;
  float bottom = isFlippedY ? textureRect.top : textureRect.bottom;

  // Если текстура валидна, и, высота или ширина не равна нулю, то рендерим
  if (image.IsValid() && (width != 0 || height != 0)) {
    // Включаем текстуринг
    glEnable(GL_TEXTURE_2D);
    image.BindTexture();
    glBegin(GL_QUADS);
      glTexCoord2f(left, top);
      glVertex2f(0, 0);

      glTexCoord2f(right, top);
      glVertex2f(width, 0);

      glTexCoord2f(right, bottom);
      glVertex2f(width, height);

      glTexCoord2f(left, bottom);
      glVertex2f(0, height);
    glEnd();
  }
  else {
    // Текстура не валидна - текстуринг не нужен
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
      glVertex2f(0, 0);
      glVertex2f(32, 0);
      glVertex2f(32, 32);
      glVertex2f(0, 32);
    glEnd();
  }
}

}
