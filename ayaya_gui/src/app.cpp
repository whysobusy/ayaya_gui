#include <GLFW/glfw3.h>
#include <map>

#include "app.h"
#include "window.h"

namespace ayaya {
std::map<GLFWwindow*, Window*> windows;

void OnError(int error, const char* desc) {}

App::App() {
  if (!glfwInit()) {
    return;
  }

  glfwSetErrorCallback(OnError);
#ifndef _WIN32
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
}

App::~App() {
  glfwTerminate();
}

void App::Key(KeyInfo const& k) {}

namespace {
bool WindowsOpen() {
  for (auto i = windows.cbegin(); i != windows.cend();) {
    if (glfwWindowShouldClose(i->first)) {
      i->second->Close();
      windows.erase(i++);
    } else {
      ++i;
    }
  }

  return !windows.empty();
}
}  // namespace

void App::Run() {
  while (WindowsOpen()) {
    glfwPollEvents();
  }
}

}  // namespace ayaya