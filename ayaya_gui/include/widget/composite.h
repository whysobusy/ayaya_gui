#pragma once

#include "widget/widget.h"

#include <array>
#include <vector>

namespace ayaya {
class CompositeBase : public Widget {
 public:
  virtual Rect Limits(BasicContext const& ctx) = 0;
  virtual void Draw(Context const& ctx);
  virtual void Layout(Context const& ctx) = 0;

  virtual Widget* HitTest(Context const& ctx, Point p);
  virtual bool Cursor(Context const& ctx, Point p);
  virtual bool Key(Context const& ctx, KeyInfo const& k);

  struct HitInfo {
    Widget* widget;
    Rect bounds;
    int index;
  };

  using Iterator = WidgetPtr*;
  using ConstIterator = WidgetPtr const*;

  virtual HitInfo HitElement(Context const& ctx, Point p) const;
  virtual Rect BoundsOf(Context const& ctx, std::size_t index) const = 0;

  // Iterator
  virtual std::size_t Size() const = 0;
  virtual Iterator begin() = 0;
  virtual ConstIterator begin() const = 0;

  Iterator end() { return begin() + Size(); }
  ConstIterator end() const { return begin() + Size(); }
  bool Empty() const { return Size() == 0; }
  WidgetPtr& operator[](std::size_t ix) { return begin()[ix]; }
  WidgetPtr const& operator[](std::size_t ix) const { return begin()[ix]; }

 private:
  // TODO
  HitInfo clickInfo_;
};

template <typename Container, typename Base>
class Composite : public Base {
 public:
  using Iterator = typename Base::Iterator;
  using ConstIterator = typename Base::ConstIterator;

  virtual std::size_t Size() const { return elements.size(); };
  virtual Iterator begin() { return &elements[0]; }
  virtual ConstIterator begin() const { return &elements[0]; }

  Container elements;
};

template <typename Base>
using VectorComposite = Composite<std::vector<WidgetPtr>, Base>;

}  // namespace ayaya
