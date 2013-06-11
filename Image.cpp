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
#include "Image.hpp"

#include <cstdio>

namespace se {
/// FIXME: Пока загружать можно только .png картинки

/**
 * @brief Конструктор
 */
Image::Image() {
  image = 0;
  isValid = false;
  width = 0;
  height = 0;
}

/**
 * @brief Деструктор
 */
Image::~Image() {
  // Nothing to do
}

/**
 * @brief Загружает изображение из файла
 *
 * @param imagePath : путь к картинке
 * @return Если картинка загрузилась то true, иначе false
 */
bool Image::LoadFromFile(std::string imagePath) {
  // Загружаем картинку, чтобы узнать ее ширину и высоту
  SOIL_load_image(imagePath.c_str(), &width, &height, NULL, SOIL_LOAD_L);

  // Если изображение имеет формат PNG
  if (imagePath.find(".png"))
    // Тогда загружаем изображение с специфичными флагами
    image = SOIL_load_OGL_texture
    (
        imagePath.c_str(),
        SOIL_LOAD_AUTO,
		    SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MULTIPLY_ALPHA
    );

  // Если изображение не получилось загрузить, возвращаем false
  if (image == 0)
    isValid = false;
  else // ? наче возвращаем true
    isValid = true;
  return isValid;
}

/**
 * @brief Bind'ит текстуру для отображения ее с помощью OpenGL
 */
void Image::BindTexture() const {
  glBindTexture(GL_TEXTURE_2D, image);

  /// TODO: Разобраться с флагами
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

/**
 * @return ширину картинки
 */
int Image::GetWidth() const {
  return width;
}

/**
 * @return высоту картинки
 */
int Image::GetHeight() const {
  return height;
}

/**
 * @return Если изображение загружено и валидно то true, иначе false
 */
bool Image::IsValid() const {
  return isValid;
}

}
