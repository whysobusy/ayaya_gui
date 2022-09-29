#include "widget/layer.h"
#include "paint/utils.h"

namespace ayaya {
Rect Layer::Limits(BasicContext const& ctx) {
  Rect limits{0.0, 0.0, fullExtent, fullExtent};
  for (auto const& elem : *this) {
    Rect el = elem->Limits(ctx);

    ClampMin(limits.left, el.left);
    ClampMin(limits.top, el.top);
    ClampMax(limits.right, el.right);
    ClampMax(limits.bottom, el.bottom);

    limits.right = std::max(limits.right, limits.left);
    limits.bottom = std::max(limits.bottom, limits.top);
  }
  return limits;
}

void Layer::Layout(Context const& ctx) {
  bounds = ctx.bounds_;
  for (std::size_t i = 0; i != Size(); ++i) {
    (*this)[i]->Layout(Context{ctx, (*this)[i].get(), BoundsOf(ctx, i)});
  }
}

CompositeBase::HitInfo Layer::HitElement(Context const& ctx, Point p) const {
  // TODO
  return HitInfo{};
}

Rect Layer::BoundsOf(Context const& ctx, std::size_t index) const {
  float width = ctx.bounds_.Width();
  float height = ctx.bounds_.Height();
  Rect limits = (*this)[index]->Limits(ctx);

  ClampMin(width, limits.left);
  ClampMax(width, limits.right);
  ClampMin(height, limits.top);
  ClampMax(height, limits.bottom);

  return {bounds.left, bounds.top, bounds.left + width, bounds.top + height};
}
}  // namespace ayaya