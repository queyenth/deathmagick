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

#include "Renderable.hpp"
#include "Input.hpp"
#include "Color.hpp"
#include "Camera.hpp"

#include <string>
#include <windows.h>
#include <windowsx.h>
#include <gl/GL.h>
#include <gl/GLU.h>

using namespace std;

namespace se {

/**
 * @brief Класс представляющий окно (Пока только под Windows)
 */
class Window {
public:

  /**
   * @brief Конструктор
   *
   * @param name : Имя окна
   * @param width : ширина окна (по умолчанию 640)
   * @param height : высота окна (по умолчанию 480)
   * @param bits : глубина окна (по умолчанию 640)
   */
  Window(wstring name, int width=640, int height=480, int bits=32);

  /**
   * @brief Метод, который создает окно, и устанавливает на него фокус
   */
  void CreateUserWindow();

  /**
   * @brief Деструктор
   */
  ~Window();

  /**
   * @brief Метод рисует объект в окно
   *
   * @param entity : указатель на рисуемый объект
   */
  void Draw(Renderable *entity);

  /**
   * @brief Переключение буфферов экрана
   */
  void Display();

  /**
   * @brief Очищает окно заданным цветом
   *
   * @param color : значение цвета, которым будет очищено окно (по умолчанию белый)
   */
  void Clear(Color color = Color(1.0f, 1.0f, 1.0f));

  /**
   * @brief Метод приема и обработки сообщений
   */
  void ProcessEvents();

  /**
   * @return если окно открыто - true, иначе false
   */
  bool IsOpened() const;

  /**
   * @brief Для real-time handling input
   *
   * @return ссылку на Input
   */
  Input& GetInput();

  /**
   * @return ссылку на Camera
   */
  Camera& GetCamera();

  /**
   * @return ширину окна
   */
  int GetWidth() const;

  /**
   * @return высоту окна
   */
  int GetHeight() const;

  /**
   * @return имя окна
   */
  wstring GetName() const;

  /**
   * @return хэндл окна
   */
  HWND GetHandle() const;
private:
  /**
   * @brief Инициализирует OpenGL
   */
  void InitGL();

  /**
   * @brief Обрабатывает сообщения, приходящие от окна
   *
   * @param uMsg : сообщение
   * @param wParam : data
   * @param lParam : data
   */
  void ProcessEvents(UINT uMsg, WPARAM wParam, LPARAM lParam);

  /**
   * @param hWnd : хэндл окна
   * @param uMsg : сообщение
   * @param wParam : data
   * @param lParam : data
   */
  static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

  /**
   * @brief Очистка
   */
  void Cleanup();

  /// Инпут окна
  Input input;

  /// Камера
  Camera camera;

  /// инстанс окна
  HINSTANCE hInstance;

  /// прямоугольная область окна
  RECT windowRect;

  /// ширина окна
  int width;

  /// высота окна
  int height;

  int bits;

  /// формат пикселя
  int PixelFormat;

  /// флаг, показывающий открыто ли окно
  bool isOpened;

  /// имя окна
  wstring nameOfWindow;

  /// хэндл окна
  HWND hWnd;

  HDC hDC;
  HGLRC hRC;
};

}
