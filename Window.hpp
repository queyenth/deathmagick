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

  Window();

  /**
   * @brief Конструктор
   *
   * @param name : Имя окна
   * @param width : ширина окна (по умолчанию 640)
   * @param height : высота окна (по умолчанию 480)
   * @param bits : глубина окна (по умолчанию 640)
   */
  Window(wstring name, int width=640, int height=480, bool fullscreen=false, int bits=32);

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

  bool IsActive() const;

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

  void SetWidth(int width);
  void SetHeight(int height);
  void SetFullscreen(bool fullscreen);

  /**
   * @return имя окна
   */
  wstring GetName() const;

  /**
   * @return хэндл окна
   */
  HWND GetHandle() const;

  HDC GetDC() const;

  void KillWindow();

  void ResizeWindow(int width, int height);
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

  /// Инпут окна
  Input input;

  /// Камера
  Camera camera;

  /// инстанс окна
  HINSTANCE hInstance;

  /// ширина окна
  int width;

  /// высота окна
  int height;

  int bits;

  /// флаг, показывающий открыто ли окно
  bool isOpened;
  bool fullscreen;
  bool isActive;

  /// имя окна
  wstring nameOfWindow;

  /// хэндл окна
  HWND hWnd;

  HDC hDC;
  HGLRC hRC;
};

}
