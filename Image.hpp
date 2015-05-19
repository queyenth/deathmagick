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
