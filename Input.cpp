#include "Input.hpp"

namespace se {

/**
 * @brief Конструктор
 */
Input::Input() {
  // Устанавливаем, что все клавиши не нажаты
  for (int i = 0; i < 256; i++)
    keys[i] = false;

  // Координаты мыши = 0; 0
  mouse.x = 0;
  mouse.y = 0;

  // Клавиши мыши не нажаты
  mouse.leftButton = false;
  mouse.rightButton = false;
}

/**
 * @brief Изменяет состояние key, на нажатие
 *
 * @param key : код клавиша
 */
void Input::PressKey(int key) {
  keys[key] = true;
}

/**
 * @brief Изменяет состояние key, на нежатость (О_о)
 *
 * @param key : код клавиши
 */
void Input::UnPressKey(int key) {
  keys[key] = false;
}

/**
 * @brief Определяет, нажата ли клавиша
 *
 * @param key : код клавиши
 * @return True, если клавиша нажата, иначе false
 */
bool Input::IsKeyPressed(int key) const {
  return keys[key];
}

/**
 * @brief Изменяет координату мыши по X
 *
 * @param x : координата по X
 */
void Input::SetMouseX(int x) {
  mouse.x = x;
}

/**
 * @brief Изменяет координату мыши по Y
 *
 * @param y : координата по Y
 */
void Input::SetMouseY(int y) {
  mouse.y = y;
}

/**
 * @return текущее положение мыши по X координате
 */
int Input::GetMouseX() const {
  return mouse.x;
}

/**
 * @return текущее положение мыши по Y координате
 */
int Input::GetMouseY() const {
  return mouse.y;
}

/**
 * @brief Устанавливает, что была нажата левая клавиша мыши
 */
void Input::PressLeftMouse() {
  mouse.leftButton = true;
}

/**
 * @brief Устанавливает, что была нажата правая клавиша мыши
 */
void Input::PressRightMouse() {
  mouse.rightButton = true;
}

/**
 * @return состояние левой кнопки мыши
 */
bool Input::IsLeftMousePressed() const {
  return mouse.leftButton;
}

/**
 * @return состояние правой кнопки мыши
 */
bool Input::IsRightMousePressed() const {
  return mouse.rightButton;
}

/**
 * @brief Устанавливает, что левая кнопки мыши больше не нажата
 */
void Input::UnPressLeftMouse() {
  mouse.leftButton = false;
}

/**
 * @brief Устанавливает, что правая кнопки мыши больше не нажата
 */
void Input::UnPressRightMouse() {
  mouse.rightButton = false;
}

}
