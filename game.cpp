#include "Window.hpp"

int main() {
  se::Window window(L"Test");

  while (window.IsOpened()) {
    window.ProcessEvents();
    window.Clear();
    // Drawing Process Here
    window.Display();
  }
  return 0;
}