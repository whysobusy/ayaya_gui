#include "widget.h"

#include <array>
#include <vector>

namespace ayaya {
class CompositeBase : public Widget {
 public:
  CompositeBase();
  ~CompositeBase();

  // render
  virtual Rect limits();
  virtual void Draw(Context const& ctx);
  virtual void Layout(Context const& ctx);
  // control
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

  virtual std::size_t Size() const = 0;
  virtual Iterator Begin() = 0;
  virtual ConstIterator Begin() const = 0;

  Iterator end() { return Begin() + Size(); }
  ConstIterator end() const { return Begin() + Size(); }
  bool empty() const { return Size() == 0; }
  WidgetPtr& operator[](std::size_t ix) { return Begin()[ix]; }
  WidgetPtr const& operator[](std::size_t ix) const { return Begin()[ix]; }

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
  virtual Iterator Begin() { return &elements[0]; }
  virtual ConstIterator Begin() const { return &elements[0]; }

  Container elements;
};

template <size_t N, typename Base>
using ArrayComposite = Composite<std::array<WidgetPtr, N>, Base>;

template <typename Base>
using VectorComposite = Composite<std::vector<WidgetPtr>, Base>;

}  // namespace ayaya
