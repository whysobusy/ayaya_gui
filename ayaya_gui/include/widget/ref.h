#pragma once

#include "widget/widget.h"

namespace ayaya {
template <typename Widget>
class WidgetRef : public Widget {
 public:
  WidgetRef(Widget&& rhs);
  WidgetRef(Widget const& rhs);

  // render
  virtual Rect Limits(BasicContext const& ctx);
  virtual void Draw(Context const& ctx);
  virtual void Layout(Context const& ctx);
  // control
  virtual Widget* HitTest(Context const& ctx, Point p);
  virtual bool Cursor(Context const& ctx, Point p);
  virtual bool Key(Context const& ctx, KeyInfo const& k);

 private:
  using WidgetPtr = std::shared_ptr<Widget>;
  WidgetPtr ptr;
};

template <typename Widget>
WidgetRef<Widget> Ref(Widget&& rhs);

template <typename Widget>
WidgetRef<Widget> Ref(Widget const& rhs);

// inlines
template <typename Widget>
inline WidgetRef<Widget>::WidgetRef(Widget&& rhs)
    : ptr(std::dynamic_pointer_cast<Widget>(New_(rhs))) {}

template <typename Widget>
inline WidgetRef<Widget>::WidgetRef(Widget const& rhs)
    : ptr(std::dynamic_pointer_cast<Widget>(New_(rhs))) {}

template <typename Widget>
inline Rect WidgetRef<Widget>::Limits(BasicContext const& ctx) const {
  return ptr->Limits(ctx);
}

template <typename Widget>
inline void WidgetRef<Widget>::Draw(context const& ctx) {
  ptr->Draw(ctx);
}

template <typename Widget>
inline void WidgetRef<Widget>::Layout(context const& ctx) {
  ptr->Layout(ctx);
}

template <typename Widget>
inline Widget* WidgetRef<Widget>::HitTest(context const& ctx, point p) {
  return ptr->HitTest(ctx, p);
}

template <typename Widget>
inline bool WidgetRef<Widget>::Key(context const& ctx, key_info const& k) {
  return ptr->key(ctx, k);
}

template <typename Widget>
inline bool WidgetRef<Widget>::Cursor(context const& ctx, point p) {
  return ptr->Cursor(ctx, p);
}

template <typename Widget>
Widget& WidgetRef<Widget>::get() {
  return *ptr.get();
}

template <typename Widget>
Widget const& WidgetRef<Widget>::get() const {
  return *ptr.get();
}

template <typename Widget>
inline WidgetRef<Widget> Ref(Widget&& rhs) {
  return {rhs};
}

template <typename Widget>
inline WidgetRef<Widget> Ref(Widget const& rhs) {
  return {rhs};
}

}  // namespace ayaya