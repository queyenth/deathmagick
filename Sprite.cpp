#include "Sprite.hpp"
#include <iostream>

namespace se {

/**
 * @brief Конструктор
 *
 * @param x : координата по X(по умолчанию 0)
 * @param y : координата по Y(по умолчанию 0)
 */
Sprite::Sprite(int x, int y, int width, int height, Color color, bool isFixed) : Renderable(x, y, width, height, color, isFixed), image() {
  
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
  float width = GetWidth()/2;
  float height = GetHeight()/2;

  float top = isFlippedY ? textureRect.bottom : textureRect.top;
  float left = isFlippedX ? textureRect.right : textureRect.left;
  float right = isFlippedX ? textureRect.left : textureRect.right;
  float bottom = isFlippedY ? textureRect.top : textureRect.bottom;

  // Если текстура валидна, и, высота или ширина не равна нулю, то рендерим
  if (image.IsValid() && (GetWidth() != 0 || GetHeight() != 0)) {
    // Включаем текстуринг
    glEnable(GL_TEXTURE_2D);
    image.BindTexture();
    glBegin(GL_QUADS);
      glTexCoord2f(left, top);
      glVertex2f(-width, -height);

      glTexCoord2f(right, top);
      glVertex2f(width, -height);

      glTexCoord2f(right, bottom);
      glVertex2f(width, height);

      glTexCoord2f(left, bottom);
      glVertex2f(-width, height);
    glEnd();
  }
  else {
    // Текстура не валидна - текстуринг не нужен
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
      glVertex2f(-width, -height);
      glVertex2f(width, -height);
      glVertex2f(width, height);
      glVertex2f(-width, height);
    glEnd();
  }
}

}
