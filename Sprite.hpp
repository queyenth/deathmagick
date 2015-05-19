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
  Sprite(int x=0, int y=0, int width=0, int height=0, Color color = Color(), bool isFixed=false);

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

  Image GetImage() const {
    return image;
  }

protected:
  mutable Image image;

private:
  /**
   * @brief Смотри Renderable::Render()
   *
   * Рисует спрайт с наложенным изображением
   */
  virtual void Render() const;
};

}
