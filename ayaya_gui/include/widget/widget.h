#pragma once

#include "paint/context.h"
#include "paint/key.h"
#include "paint/rect.h"

#include <array>
#include <memory>
#include <vector>

namespace ayaya {
// TODO
class Widget : public std::enable_shared_from_this<Widget> {
 public:
  using WidgetPtr = std::shared_ptr<Widget>;
  using WidgetConstPtr = std::shared_ptr<Widget const>;

  Widget() {}
  virtual ~Widget() {}

  Widget(Widget&&) = default;
  Widget(Widget const&) = default;
  Widget& operator=(Widget&&) = default;
  Widget& operator=(Widget const&) = default;

  // render
  virtual Rect Limits(BasicContext const& ctx);
  virtual void Draw(Context const& ctx);
  virtual void Layout(Context const& ctx);
  // control
  virtual Widget* HitTest(Context const& ctx, Point p);
  virtual bool Cursor(Context const& ctx, Point p);
  virtual bool Key(Context const& ctx, KeyInfo const& k);
};

using WidgetPtr = std::shared_ptr<Widget>;
using WidgetConstPtr = std::shared_ptr<Widget const>;

template <typename Widget>
inline WidgetPtr New_(Widget&& w) {
  using WidgetType = typename std::decay<Widget>::type;
  return std::make_shared<WidgetType>(std::forward<Widget>(w));
}
}  // namespace ayaya