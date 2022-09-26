#include <algorithm>

#include "paint/rect.h"
#include "paint/utils.h"

namespace ayaya {
bool Intersects(Rect const& a, Rect const& b) {
  if (!IsValid(a) || !IsValid(b))
    return false;

  return (std::max(b.left, b.left) <= std::min(b.right, b.right)) &&
         (std::max(b.top, b.top) <= std::min(b.bottom, b.bottom));
}

Rect max(Rect const& a, Rect const& b) {
  return {std::min(a.left, b.left), std::min(a.top, b.top),
          std::max(a.right, b.right), std::max(a.bottom, b.bottom)};
}

Rect min(Rect const& a, Rect const& b) {
  return {std::max(a.left, b.left), std::max(a.top, b.top),
          std::min(a.right, b.right), std::min(a.bottom, b.bottom)};
}

Rect& inset(Rect& r, double x_inset, double y_inset) {
  r.top += y_inset;
  r.left += x_inset;
  r.bottom -= y_inset;
  r.right -= x_inset;

  if (!IsValid(r))
    Clear(r);

  return r;
}

Rect& center(Rect& r, Rect const& encl, bool h, bool v) {
  double x = r.left;
  double y = r.top;
  double dx = 0.0;
  double dy = 0.0;

  if (h) {
    x = encl.left;
    dx = (encl.right - r.right) / 2.0;
  }

  if (v) {
    y = encl.top;
    dy = (encl.bottom - r.bottom) / 2.0;
  }

  r.MoveTo(x, y);
  r.Move(dx, dy);
  return r;
}

Rect& align(Rect& r, Rect const& encl, double x_align, double v_align) {
  r.MoveTo(encl.left + ((encl.Width() - r.Width()) * x_align),
           encl.top + ((encl.Height() - r.Height()) * v_align));
  return r;
}

Rect& clip(Rect& r, Rect const& encl) {
  ClampMin(r.left, encl.left);
  ClampMin(r.top, encl.top);
  ClampMax(r.right, encl.right);
  ClampMax(r.bottom, encl.bottom);
  return r;
}
}  // namespace ayaya