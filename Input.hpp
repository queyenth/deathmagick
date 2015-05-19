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
  bool IsKeyPressed(int) const;

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
