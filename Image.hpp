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
#include <string>
#include <Windows.h>
#include <gl/gl.h>
#include <SOIL.h>

namespace se {

/**
 * @brief Реализует изображение
 */
class Image {
public:
  /**
   * @brief Конструктор
   */
  Image();

  /**
   * @brief Деструктор
   */
  ~Image();

  /**
   * @brief Загружает изображение из файла
   *
   * @param imagePath : путь к картинке
   * @return Если картинка загрузилась то true, иначе false
   */
  bool LoadFromFile(std::string imagePath);

  /**
   * @brief Bind'ит текстуру для отображения ее с помощью OpenGL
   */
  void BindTexture() const;

  /**
   * @return ширину картинки
   */
  int GetWidth() const;

  /**
   * @return высоту картинки
   */
  int GetHeight() const;

  /**
   * @return Если изображение загружено и валидно то true, иначе false
   */
  bool IsValid() const;
private:

  /// Переменная для хранение изображения
  GLuint image;

  /// Ширина картинки
  int width;

  /// Высота картинки
  int height;

  /// Флаг, обозначающий валидность изображения
  bool isValid;
};

}
