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
#include "Window.hpp"

namespace se {

/**
 * @param hWnd : хэндл окна
 * @param uMsg : сообщение
 * @param wParam : data
 * @param lParam : data
 */
LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  if (uMsg == WM_CREATE) {
    long This = reinterpret_cast<long>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
    SetWindowLongPtr(hWnd, GWLP_USERDATA, This);
  }

  Window *window = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

  if (window) {
    window->ProcessEvents(uMsg, wParam, lParam);
  }

  if (uMsg == WM_CLOSE)
    return 0;

  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/**
 * @brief Деструктор
 */
Window::~Window() {
  if (hWnd)
    DestroyWindow(hWnd);

  if (hWnd)
    DestroyWindow(hWnd);
  UnregisterClass(nameOfWindow.c_str(), GetModuleHandle(NULL));
}

/**
 * @brief Конструктор
 *
 * @param name : Имя окна
 * @param width : ширина окна (по умолчанию 640)
 * @param height : высота окна (по умолчанию 480)
 * @param bits : глубина окна (по умолчанию 640)
 */
Window::Window(wstring name, int width, int height, int bits) : camera(0, 0) {
  hWnd = NULL;
  hInstance = GetModuleHandle(NULL);
  this->width = width;
  this->height = height;
  this->bits = bits;
  nameOfWindow = name;
  isOpened = true;
  windowRect.left = (long)0;
  windowRect.right = (long)width;
  windowRect.top = (long)0;
  windowRect.bottom = (long)height;
  AdjustWindowRectEx(&windowRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
  CreateUserWindow();
  InitGL();
}

/**
 * @brief Метод, который создает окно, и устанавливает на него фокус
 */
void Window::CreateUserWindow() {
  WNDCLASS wc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc.hInstance = hInstance;
  wc.hbrBackground = NULL;
  wc.lpfnWndProc = (WNDPROC)&Window::WndProc;
  wc.lpszClassName = nameOfWindow.c_str();
  wc.lpszMenuName = NULL;
  wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

  RegisterClass(&wc);

  hWnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
      wc.lpszClassName, wc.lpszClassName,
      WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
      0, 0,
      windowRect.right - windowRect.left,
      windowRect.bottom - windowRect.top,
      NULL, NULL, hInstance, this);

  static PIXELFORMATDESCRIPTOR pfd =
  {
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW |
    PFD_SUPPORT_OPENGL |
    PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,
    (BYTE)bits,
    0, 0, 0, 0, 0, 0,
    0,
    0,
    0,
    0, 0, 0, 0,
    16,
    0,
    0,
    PFD_MAIN_PLANE,
    0,
    0, 0, 0
  };

  hDC = GetDC(hWnd);
  PixelFormat = ChoosePixelFormat(hDC, &pfd);
  SetPixelFormat(hDC, PixelFormat, &pfd);
  hRC = wglCreateContext(hDC);
  wglMakeCurrent(hDC, hRC);

  ShowWindow(hWnd, SW_SHOW);
  SetForegroundWindow(hWnd);
  SetFocus(hWnd);
}

/**
 * @brief Метод приема и обработки сообщений
 */
void Window::ProcessEvents() {
  MSG msg;
  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

/**
 * @brief Обрабатывает сообщения, приходящие от окна
 *
 * @param uMsg : сообщение
 * @param wParam : data
 * @param lParam : data
 */
void Window::ProcessEvents(UINT uMsg, WPARAM wParam, LPARAM lParam) {
  if (hWnd == NULL)
    return ;

  switch (uMsg) {
    case WM_KEYDOWN:
      input.PressKey(wParam);
      break;
    case WM_KEYUP:
      input.UnPressKey(wParam);
      break;
    case WM_LBUTTONDOWN:
      input.PressLeftMouse();
      break;
    case WM_RBUTTONDOWN:
      input.PressRightMouse();
      break;
    case WM_LBUTTONUP:
      input.UnPressLeftMouse();
      break;
    case WM_RBUTTONUP:
      input.UnPressRightMouse();
      break;
    case WM_MOUSEMOVE:
      input.SetMouseX(GET_X_LPARAM(lParam));
      input.SetMouseY(GET_Y_LPARAM(lParam));
      break;
    case WM_CLOSE:
      isOpened = false;
      Cleanup();
      break;
    default:
      break;
  }
}

/**
 * @brief Очистка
 */
void Window::Cleanup() {
  ShowCursor(TRUE);
  if (hRC) {
    wglDeleteContext(hRC);
    hRC = NULL;
  }
  if (hDC) {
    ReleaseDC(hWnd, hDC);
    hDC = NULL;
  }
}

/**
 * @return если окно открыто - true, иначе false
 */
bool Window::IsOpened() const {
  return isOpened;
}

/**
 * @brief Инициализирует OpenGL
 */
void Window::InitGL() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
  glShadeModel(GL_SMOOTH);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glViewport(0, 0, width, height);
  glOrtho(0, width, 0, height, 0, 1);
}

/**
 * @brief Метод рисует объект в окно
 *
 * @param entity : указатель на рисуемый объект
 */
void Window::Draw(Renderable *entity) {
  // Смотри Renderable::Draw
  entity->Draw(camera);
}

/**
 * @brief Переключение буфферов экрана
 */
void Window::Display() {
  SwapBuffers(hDC);
  camera.SetChanged(false);
}

/**
 * @brief Очищает окно заданным цветом
 *
 * @param color : значение цвета, которым будет очищено окно (по умолчанию белый)
 */
void Window::Clear(Color color) {
  glClearColor(color.GetRed(), color.GetGreen(), color.GetBlue(), 0.5f);
  glClear(GL_COLOR_BUFFER_BIT);
}

/**
 * @brief Для real-time handling input
 *
 * @return ссылку на Input
 */
Input& Window::GetInput() {
  return input;
}

/**
 * @return ссылку на Camera
 */
Camera& Window::GetCamera() {
  return camera;
}

/**
 * @return ширину окна
 */
int Window::GetWidth() const {
	return width;
}

/**
 * @return высоту окна
 */
int Window::GetHeight() const {
	return height;
}

/**
 * @return имя окна
 */
wstring Window::GetName() const {
	return nameOfWindow;
}

/**
 * @return хэндл окна
 */
HWND Window::GetHandle() const {
  return hWnd;
}

}
