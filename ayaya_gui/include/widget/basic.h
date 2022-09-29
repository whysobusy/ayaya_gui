#pragma once

#include "widget/widget.h"

namespace ayaya {
class Panel : public Widget {
 public:
  static float cornerRadius;
  static Rect shadowOffset;
  virtual void Draw(Context const& ctx);
};

class TitleBar : public Widget {
 public:
  static float cornerRadius;
  virtual void Draw(Context const& ctx);
};
}  // namespace ayaya