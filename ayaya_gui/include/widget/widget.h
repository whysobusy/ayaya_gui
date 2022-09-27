#pragma once

#include "paint/key.h"
#include "paint/rect.h"

#include <array>
#include <memory>
#include <vector>

namespace ayaya {
// TODO
class Widget : public std::enable_shared_from_this<Widget> {
 public:
  Widget() {}
  virtual ~Widget() {}

  Widget(Widget&&) = default;
  Widget(Widget const&) = default;
  Widget& operator=(Widget&&) = default;
  Widget& operator=(Widget const&) = default;

  // render
  virtual Rect limits();
  virtual void Draw(context const& ctx);
  virtual void Layout(context const& ctx);
  // control
  virtual Widget* HitTest(context const& ctx, point p);
  virtual bool Key(context const& ctx, KeyInfo const& k);
};
}  // namespace ayaya