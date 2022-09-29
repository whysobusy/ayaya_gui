#include "widget/basic.h"

namespace ayaya {
float Panel::cornerRadius = 3.0;
Rect Panel::shadowOffset = {-10, -10, +20, +30};

void Panel::Draw(Context const& ctx) {
  auto& canvas = ctx.canvas_;
  auto save = canvas.NewState();
  auto const& bounds = ctx.bounds_;

  canvas.BeginPath();
  canvas.AddRect(bounds);
  canvas.FillStyle(Color::Blue());
  canvas.Fill();
}

float TitleBar::cornerRadius = 3.0;

void TitleBar::Draw(Context const& ctx) {
  auto& canvas = ctx.canvas_;
  auto const& bounds = ctx.bounds_;

  // TODO
}
}  // namespace ayaya