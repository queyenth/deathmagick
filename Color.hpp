#pragma once

namespace se {

/**
 * @brief Класс, описывающий цвет
 *
 * Каждый цвет должен быть в диапозоне от 0.0 до 1.0
 */
class Color {
public:
  /**
   * @brief Конструктор
   *
   * @param r : красный цвет (по умолчанию 1.0)
   * @param g : зеленый цвет (по умолчанию 1.0)
   * @param b : синий цвет (по умолчанию 1.0)
   */
  Color(float r=1.0f, float g=1.0f, float b=1.0f, float a=0.0f);

  /**
   * @return Значение красного цвета
   */
  float GetRed() const;

  /**
   * @return Значение зеленого цвета
   */
  float GetGreen() const;

  /**
   * @return Значение синего цвета
   */
  float GetBlue() const;

  float GetAlpha() const;

  /**
   * @brief Устанавливает новое значение красного цвета
   *
   * @param r : значение красного цвета
   */
  void SetRed(float r);

  /**
   * @brief Устанавливает новое значение зеленого цвета
   *
   * @param g : значение зеленого цвета
   */
  void SetGreen(float g);

  /**
   * @brief Устанавливает новое значение синего цвета
   *
   * @param b : значение синего цвета
   */
  void SetBlue(float b);

  void SetAlpha(float a);

  bool operator==(Color &right) {
    if (r == right.r && g == right.g && b == right.b && a == right.a)
      return true;
    else
      return false;
  }

  void operator*(Color &right) {
    r *= right.r;
    g *= right.g;
    b *= right.b;
    a *= right.a;
  }

  friend se::Color &operator*=(se::Color &left, se::Color &right) {
    left.r *= right.r;
    left.g *= right.g;
    left.b *= right.b;
    left.a *= right.a;
    return left;
  }

  /**
   * @brief Предустановленный белый цвет
   */
  static const Color White;
  /**
   * @brief Предустановленный черный цвет
   */
  static const Color Black;
  /**
   * @brief Предустановленный красный цвет
   */
  static const Color Red;
  /**
   * @brief Предустановленный зеленый цвет
   */
  static const Color Green;
  /**
   * @brief Предустановленный синий цвет
   */
  static const Color Blue;
private:
  /** Должен быть [0;1] */
  float r;

  /** Должен быть [0;1] */
  float g;

  /** Должен быть [0;1] */
  float b;

  /** Должен быть [0;1] */
  float a;
};

}
