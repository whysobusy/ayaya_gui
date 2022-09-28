#include "composite.h"

namespace ayaya {
class Layer : CompositeBase {
 public:
  virtual Rect Limits(BasicContext const& ctx) const;
  virtual void Layout(Context const& ctx);
  virtual HitInfo HitElement(Context const& ctx, Point p) const;
  virtual Rect BoundsOf(Context const& ctx, std::size_t index) const;

 private:
  Rect bounds;
};

using LayerComposite = VectorComposite<Layer>
}  // namespace ayaya