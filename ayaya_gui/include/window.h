#pragma once

#include <GLFW/glfw3.h>

#include "app.h"
#include "paint/color.h"
#include "paint/key.h"
#include "paint/point.h"

namespace ayaya {
class Window {
 public:
  Window(char const* title, Point size, Color backGroundColor, App& app);
  ~Window();

  Window(Window const&) = delete;
  Window& operator=(Window const&) = delete;

  virtual void Draw();
  virtual void Key(KeyInfo const& k);
  virtual void Close();

 private:
  Color backGroundColor_;
  GLFWwindow* window_;
};
}  // namespace ayaya