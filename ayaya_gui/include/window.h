#pragma once

#include <GLFW/glfw3.h>
#include "skia/core/SkSurface.h"
#include "skia/gpu/GrDirectContext.h"

#include "app.h"
#include "paint/canvas.h"
#include "paint/color.h"
#include "paint/key.h"
#include "paint/point.h"
#include "paint/rect.h"
#include "widget/layer.h"

namespace ayaya {
class Window {
 public:
  Window(char const* title, double width, double height, Color backGroundColor);
  ~Window();

  Window(Window const&) = delete;
  Window& operator=(Window const&) = delete;

  virtual void Render();
  virtual void Draw(Canvas& cnv, int width, int height);
  virtual void Key(KeyInfo const& k);
  Point CursorPos() const;
  Point Size() const;
  virtual void Close();

  VectorComposite<Layer> content;

 private:
  Color backGroundColor_;
  GLFWwindow* window_;
  Rect currentLimits_;
  Rect currentBounds_;
  // TODO
  GrDirectContext* skContext_;
  // TODO
  SkSurface* skSurface_;
};

inline Point CursorPos(Window const& window)  // declared in context.hpp
{
  return window.CursorPos();
}

inline Rect ViewBounds(Window const& window) {
  auto size = window.Size();
  return {0, 0, size.x, size.y};
}
}  // namespace ayaya