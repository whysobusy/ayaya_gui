#include "window.h"

#define NANOVG_GL3_IMPLEMENTATION
#include <map>

namespace ayaya {
extern std::map<GLFWwindow*, Window*> windows;

void WindowRefresh(GLFWwindow* window) {}

Window::Window(char const* title, Point size, Color backGroundColor, App& app)
    : backGroundColor_(backGroundColor) {
  window_ = glfwCreateWindow(size.x, size.y, title, 0, 0);
  if (window_ == 0) {
    glfwTerminate();
    return;
  }

  glfwSetWindowUserPointer(window_, this);
  glfwSetWindowRefreshCallback(window_, WindowRefresh);
  glfwMakeContextCurrent(window_);

  glfwSwapInterval(0);
  glfwSetTime(0);

  windows[window_] = this;
}

Window::~Window() {
  windows.erase(window_);
  glfwDestroyWindow(window_);
}

void Window::Draw() {
  double mx, my;
  glfwGetCursorPos(window_, &mx, &my);

  int w_width, w_height;
  glfwGetWindowSize(window_, &w_width, &w_height);

  int fb_width, fb_height;
  glfwGetFramebufferSize(window_, &fb_width, &fb_height);

  // Update and render
  glViewport(0, 0, fb_width, fb_height);
  glClearColor(backGroundColor_.red, backGroundColor_.green,
               backGroundColor_.blue, backGroundColor_.alpha);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  // Calculate pixel ration for hi-dpi devices.
  float px_ratio = (float)fb_width / (float)w_width;
  glfwSwapBuffers(window_);
}

void Window::Key(KeyInfo const& k) {}

void Window::Close() {}
}  // namespace ayaya