#pragma once

#include "paint/canvas.h"

#include <functional>
#include <string>

namespace ayaya {
class Window;
class Widget;

Point CursorPos(Window const& window);
Rect ViewBounds(Window const& window);
Point DeviceToUser(Point p, Canvas& cnv);
Rect DeviceToUser(Rect const& r, Canvas& cnv);

struct BasicContext {
  BasicContext(Window& window, Canvas& cnv) : window_(window), canvas_(cnv) {}

  BasicContext(BasicContext const&) = default;
  BasicContext& operator=(BasicContext const&) = delete;

  Rect ViewBounds() const {
    return canvas_.DeviceToUser(ayaya::ViewBounds(window_));
  }

  Point cursor_pos() const { return canvas_.DeviceToUser(CursorPos(window_)); }

  ayaya::Window& window_;
  ayaya::Canvas& canvas_;
};

class Context : public BasicContext {
 public:
  Context(Context const& rhs, Rect _bounds)
      : BasicContext(rhs.window_, rhs.canvas_),
        widget_(rhs.widget_),
        parent_(rhs.parent_),
        bounds_(_bounds) {}

  Context(Context const& parent, Widget* _widget, Rect _bounds)
      : BasicContext(parent.window_, parent.canvas_),
        widget_(_widget),
        parent_(&parent),
        bounds_(_bounds) {}

  Context(class Window& _window,
          class Canvas& _canvas,
          Widget* _widget,
          Rect _bounds)
      : BasicContext(_window, _canvas),
        widget_(_widget),
        parent_(nullptr),
        bounds_(_bounds) {}

  Context(Context const&) = default;
  Context& operator=(Context const&) = delete;

  Widget* widget_;
  Context const* parent_;
  Rect bounds_;

 private:
  // TODO add listener
  using listener_function =
      std::function<void(Context const& ctx, Widget* widget, std::string what)>;

  listener_function listener_;
};
}  // namespace ayaya