#include "widget/composite.h"
#include "window.h "

namespace ayaya {

namespace {
Rect WindowBounds(Window const& win) {
  auto size = win.Size();
  return Rect{0, 0, size.x, size.y};
}
}  // namespace

void CompositeBase::Draw(Context const& ctx) {
  auto windowBounds = WindowBounds(ctx.window_);
  for (std::size_t i = 0; i < Size(); ++i) {
    Rect bounds = BoundsOf(ctx, i);
    if (Intersects(bounds, windowBounds)) {
      auto elem = (*this)[i];
      Context ectx(ctx, elem.get(), bounds);
      elem->Draw(ectx);
    }
  }
}

Widget* CompositeBase::HitTest(Context const& ctx, Point p) {
  if (!Empty()) {
    HitInfo info = HitElement(ctx, p);
    return info.widget;
  }
}

bool CompositeBase::Cursor(Context const& ctx, Point p) {
  // TODO
  return false;
}
bool CompositeBase::Key(Context const& ctx, KeyInfo const& k) {
  // TODO
  return false;
}

CompositeBase::HitInfo CompositeBase::HitElement(Context const& ctx,
                                                 Point p) const {
  for (std::size_t i = 0; i < Size(); ++i) {
    WidgetPtr e = (*this)[i];
    // TODO
  }
  return HitInfo{};
}
}  // namespace ayaya