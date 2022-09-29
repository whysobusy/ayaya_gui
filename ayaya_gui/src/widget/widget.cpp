#include "widget/widget.h"
#include "paint/utils.h"

namespace ayaya {
Rect Widget::Limits(BasicContext const& ctx) {
  return fullLimits;
}

void Widget::Draw(Context const& ctx) {}

void Widget::Layout(Context const& ctx) {}

Widget* Widget::HitTest(Context const& ctx, Point p) {
  return (ctx.bounds_.Includes(p)) ? this : 0;
}

bool Widget::Cursor(Context const& ctx, Point p) {
  return false;
}

bool Widget::Key(Context const& ctx, KeyInfo const& k) {
  return false;
}
}  // namespace ayaya