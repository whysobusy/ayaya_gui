#pragma once

#include <GLFW/glfw3.h>
#include "skia/core/SkSurface.h"
#include "skia/gpu/GrDirectContext.h"

#include "app.h"
#include "paint/color.h"
#include "paint/key.h"
#include "paint/point.h"

namespace ayaya {
class Window {
 public:
  Window(char const* title, double width, double height, Color backGroundColor);
  ~Window();

  Window(Window const&) = delete;
  Window& operator=(Window const&) = delete;

  virtual void Draw();
  virtual void Key(KeyInfo const& k);
  virtual void Close();

 private:
  Color backGroundColor_;
  GLFWwindow* window_;
  // TODO
  GrDirectContext* skContext_;
  // TODO
  SkSurface* skSurface_;
};
}  // namespace ayaya