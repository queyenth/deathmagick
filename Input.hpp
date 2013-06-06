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
 * @brief Класс, для удобного handlinga мыши и клавиатуры
 */
class Input {
public:
  /**
   * @brief Конструктор
   */
  Input();

  /**
   * @brief Изменяет состояние key, на нажатие
   *
   * @param key : код клавиша
   */
  void PressKey(int);

  /**
   * @brief Определяет, нажата ли клавиша
   *
   * @param key : код клавиши
   * @return True, если клавиша нажата, иначе false
   */
  bool IsKeyPressed(int);

  /**
   * @brief Изменяет состояние key, на нежатость (О_о)
   *
   * @param key : код клавиши
   */
  void UnPressKey(int);

  /**
   * @brief Изменяет координату мыши по X
   *
   * @param x : координата по X
   */
  void SetMouseX(int);

  /**
   * @brief Изменяет координату мыши по Y
   *
   * @param y : координата по Y
   */
  void SetMouseY(int);

  /**
   * @return текущее положение мыши по X координате
   */
  int GetMouseX() const;

  /**
   * @return текущее положение мыши по Y координате
   */
  int GetMouseY() const;

  /**
   * @brief Устанавливает, что была нажата левая клавиша мыши
   */
  void PressLeftMouse();

  /**
   * @return состояние левой кнопки мыши
   */
  bool IsLeftMousePressed() const;

  /**
   * @brief Устанавливает, что была нажата правая клавиша мыши
   */
  void PressRightMouse();

  /**
   * @return состояние правой кнопки мыши
   */
  bool IsRightMousePressed() const;

  /**
   * @brief Устанавливает, что левая кнопки мыши больше не нажата
   */
  void UnPressLeftMouse();

  /**
   * @brief Устанавливает, что правая кнопки мыши больше не нажата
   */
  void UnPressRightMouse();

private:
  /// Массив всех клавиш клавиатуры
  bool keys[256];

  /**
   * @brief Структура мыши
   */
  struct {
    /// Положение мыши по X и Y координате
    int x,y;

    /// Флаг, определяющий, нажата ли левая клавиша
    bool leftButton;

    /// Флаг, определяющий, нажата ли правая клавиша
    bool rightButton;
  } mouse;
};

}
