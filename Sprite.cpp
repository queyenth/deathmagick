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
  unsigned int width = GetWidth();
  unsigned int height = GetHeight();

  unsigned int top = isFlippedY ? textureRect.bottom : textureRect.top;
  unsigned int left = isFlippedX ? textureRect.right : textureRect.left;
  unsigned int right = isFlippedX ? textureRect.left : textureRect.right;
  unsigned int bottom = isFlippedY ? textureRect.top : textureRect.bottom;

  // Если текстура валидна, и, высота или ширина не равна нулю, то рендерим
  if (image.IsValid() && (width != 0 || height != 0)) {
    // Включаем текстуринг
    glEnable(GL_TEXTURE_2D);
    image.BindTexture();
    glBegin(GL_QUADS);
      glTexCoord2i(left, top);
      glVertex2i(0, 0);

      glTexCoord2i(right, top);
      glVertex2i(width, 0);

      glTexCoord2i(right, bottom);
      glVertex2i(width, height);

      glTexCoord2i(left, bottom);
      glVertex2i(0, height);
    glEnd();
  }
  else {
    // Текстура не валидна - текстуринг не нужен
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
      glVertex2i(0, 0);
      glVertex2i(32, 0);
      glVertex2i(32, 32);
      glVertex2i(0, 32);
    glEnd();
  }
}

}
