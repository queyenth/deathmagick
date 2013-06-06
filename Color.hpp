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
  Color(float r=1.0f, float g=1.0f, float b=1.0f);

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

  bool operator==(Color right) {
    if (this->r == right.r && this->g == right.g && this->b == right.b)
      return true;
    else
      return false;
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
};

}
