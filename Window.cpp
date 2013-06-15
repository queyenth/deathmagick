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
  KillWindow();
}

/**
 * @brief Конструктор
 *
 * @param name : Имя окна
 * @param width : ширина окна (по умолчанию 640)
 * @param height : высота окна (по умолчанию 480)
 * @param bits : глубина окна (по умолчанию 640)
 */
Window::Window(wstring name, unsigned int width, unsigned int height, bool fullscreen, int bits) : camera(0, 0) {
  hWnd = NULL;
  hInstance = GetModuleHandle(NULL);
  this->width = width;
  this->height = height;
  this->bits = bits;
  this->fullscreen = fullscreen;
  isActive = true;
  nameOfWindow = name;
  isOpened = true;
  CreateUserWindow();
}

/**
 * @brief Метод, который создает окно, и устанавливает на него фокус
 */
void Window::CreateUserWindow() {
  WNDCLASSEX wc;
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
  wc.cbSize = sizeof(wc);
  wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
  
  if (!RegisterClassEx(&wc)) {
    MessageBox(NULL, L"Failed To Register A Window Class.", nameOfWindow.c_str(), MB_OK | MB_ICONEXCLAMATION);
    exit(1);
  }

  if (fullscreen) {
    DEVMODE dm;
    memset(&dm, 0, sizeof(dm));
    dm.dmSize = sizeof(dm);
    dm.dmBitsPerPel = bits;
    dm.dmPelsHeight = height;
    dm.dmPelsWidth = width;
    dm.dmFields = DM_BITSPERPEL | DM_PELSHEIGHT | DM_PELSWIDTH;
    if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
      if (MessageBox(NULL, L"Fullscreen doesn't support.\nRun in windowed mode?", nameOfWindow.c_str(), MB_YESNO | MB_ICONEXCLAMATION)==IDYES)
        fullscreen = false;
      else {
        MessageBox(NULL, L"Programm Will Now Close", nameOfWindow.c_str(), MB_OK | MB_ICONSTOP);
        exit(1);
      }
    }
  }

  DWORD dwExStyle = WS_EX_APPWINDOW;
  DWORD dwStyle;

  if (fullscreen) {
    dwStyle = WS_POPUP;
    ShowCursor(FALSE);
  }
  else {
    dwExStyle |= WS_EX_WINDOWEDGE;
    dwStyle = WS_OVERLAPPEDWINDOW;
  }

  RECT windowRect;
  windowRect.left = (long)0;
  windowRect.right = (long)width;
  windowRect.top = (long)0;
  windowRect.bottom = (long)height;

  AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

  if (!(hWnd = CreateWindowEx(dwExStyle,
      wc.lpszClassName, wc.lpszClassName,
      dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
      0, 0,
      windowRect.right - windowRect.left,
      windowRect.bottom - windowRect.top,
      NULL, NULL, hInstance, this))) {
        KillWindow();
        MessageBox(NULL, L"Failed To Create a Window.", nameOfWindow.c_str(), MB_OK | MB_ICONEXCLAMATION);
        exit(1);
  }

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

  if (!(hDC = ::GetDC(hWnd))) {
    KillWindow();
    MessageBox(NULL, L"Can't Create A GL Device Context", nameOfWindow.c_str(), MB_OK | MB_ICONEXCLAMATION);
    exit(1);
  }

  GLuint PixelFormat;
  if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd))) {
    KillWindow();
    MessageBox(NULL, L"Can't Find A Suitable PixelFormat.", nameOfWindow.c_str(), MB_OK | MB_ICONEXCLAMATION);
    exit(1);
  }

  if (!SetPixelFormat(hDC, PixelFormat, &pfd)) {
    KillWindow();
    MessageBox(NULL, L"Can't Set The PixelFormat", nameOfWindow.c_str(), MB_OK | MB_ICONEXCLAMATION);
    exit(1);
  }

  if (!(hRC = wglCreateContext(hDC))) {
    KillWindow();
    MessageBox(NULL, L"Can't Create A GL Rendering Context", nameOfWindow.c_str(), MB_OK | MB_ICONEXCLAMATION);
    exit(1);
  }

  if (!wglMakeCurrent(hDC, hRC)) {
    KillWindow();
    MessageBox(NULL, L"Can't Activate The GL Rendering Context", nameOfWindow.c_str(), MB_OK | MB_ICONEXCLAMATION);
    exit(1);
  }

  ShowWindow(hWnd, SW_SHOW);
  SetForegroundWindow(hWnd);
  SetFocus(hWnd);
  ResizeWindow(width, height);
  InitGL();
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
    case WM_MOUSEMOVE:
      input.SetMouseX(GET_X_LPARAM(lParam));
      input.SetMouseY(GET_Y_LPARAM(lParam));
      break;
    case WM_KEYDOWN:
      input.PressKey(wParam);
      break;
    case WM_KEYUP:
      input.UnPressKey(wParam);
      break;
    case WM_LBUTTONDOWN:
      input.PressLeftMouse();
      break;
    case WM_LBUTTONUP:
      input.UnPressLeftMouse();
      break;
    case WM_RBUTTONDOWN:
      input.PressRightMouse();
      break;
    case WM_RBUTTONUP:
      input.UnPressRightMouse();
      break;
    case WM_ACTIVATE:
      if (!HIWORD(wParam))
        isActive = true;
      else
        isActive = false;
      break;
    case WM_CLOSE:
      isOpened = false;
      break;
    case WM_SIZE:
      ResizeWindow(LOWORD(lParam), HIWORD(lParam));
      break;
    case WM_SYSCOMMAND:
      switch (wParam) {
      case SC_SCREENSAVE:
      case SC_MONITORPOWER:
        break;
      }
      break;
    default:
      break;
  }
}

void Window::ResizeWindow(int width, int height) {
  glViewport(0, 0, width, height);
}

void Window::KillWindow() {
  if (fullscreen) {
    ChangeDisplaySettings(NULL, 0);
    ShowCursor(TRUE);
  }
  if (hRC) {
    if (!wglMakeCurrent(NULL, NULL))
      MessageBox(NULL, L"Release Of DC And RC Failed.", nameOfWindow.c_str(), MB_OK | MB_ICONINFORMATION);
    if (!wglDeleteContext(hRC))
      MessageBox(NULL, L"Release Rendering Context Failed.", nameOfWindow.c_str(), MB_OK | MB_ICONINFORMATION);
    hRC = NULL;
  }
  if (hDC && !ReleaseDC(hWnd, hDC)) {
    MessageBox(NULL, L"Release Of Device Context Failed.", nameOfWindow.c_str(), MB_OK | MB_ICONINFORMATION);
    hDC = NULL;
  }
  if (hWnd && !DestroyWindow(hWnd)) {
    MessageBox(NULL, L"Could Not Release Window.", nameOfWindow.c_str(), MB_OK | MB_ICONINFORMATION);
    hWnd = NULL;
  }
  if (!UnregisterClass(nameOfWindow.c_str(), hInstance)) {
    MessageBox(NULL, L"Could Not Unregister Class.", nameOfWindow.c_str(), MB_OK | MB_ICONINFORMATION);
    hInstance = NULL;
  }
}

/**
 * @return если окно открыто - true, иначе false
 */
bool Window::IsOpened() const {
  return isOpened;
}

bool Window::IsActive() const {
  return isActive;
}

/**
 * @brief Инициализирует OpenGL
 */
void Window::InitGL() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
  glShadeModel(GL_SMOOTH);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
const Input& Window::GetInput() {
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
unsigned int Window::GetWidth() const {
	return width;
}

/**
 * @return высоту окна
 */
unsigned int Window::GetHeight() const {
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

HDC Window::GetDC() const {
  return hDC;
}

}
