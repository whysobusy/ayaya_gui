ifndef AYAYA
#define AYAYA

namespace Ayaya {
  struct Rect {
    constexpr Rect();
    constexpr Rect(float left, float top, float right, float bottom);

    Rect& operator=(Rect const&) = default;

    bool operator==(Rect const& other) const;
    bool operator!=(Rect const& other) const;

    bool is_empty();
    float width() const;
    void width(float width_);
    float height() const;
    void height(float height_);

    Point top_left() const;
    Point bottom_right() const;
    Point top_right() const;
    Point bottom_left() const;

    Rect move(float dx, float dy) const;
    Rect move_to(float x, float y) const;
    Rect inset(float x_inset = 1.0, float y_inset = 1.0) const;

    float top;
    float left;
    float bottom;
    float right;
  };

  //Utils
  bool is_valid(Rect r);
  bool is_same_size(Rect a, Rect b);
  bool intersects(Rect a, Rect b);

  Point center_point(Rect r);
  float area(Rect r);
  Rect max(Rect a, Rect b);
  Rect min(Rect a, Rect b);

  void clear(Rect & r);
  Rect center(Rect r, Rect encl);
  Rect center_h(Rect r, Rect encl);
  Rect center_v(Rect r, Rect encl);
  Rect align(Rect r, Rect encl, float x_align, float y_align);
  Rect align_h(Rect r, Rect encl, float x_align);
  Rect align_v(Rect r, Rect encl, float y_align);
  Rect clip(Rect r, Rect encl);

  //Inlines
  inline constexpr Rect::Rect()
      : left(0, 0), top(0, 0), right(0, 0), bottom(0, 0) {}

  inline constexpr Rect::Rect(float left, float top, float right, float bottom)
      : left(left), top(top), right(right), bottom(bottom) {}

  inline bool Rect::operator==(rect const& other) const {
    return (top == other.top) && (bottom == other.bottom) &&
           (left == other.left) && (right == other.right);
  }

  inline bool Rect::operator!=(rect const& other) const {
    return !(*this == other);
  }

  inline bool Rect::is_empty() const {
    return (left == right) || (top == bottom);
  }

  inline bool Rect::includes(point p) const {
    return (p.x >= left) && (p.x <= right) && (p.y >= top) && (p.y <= bottom);
  }

  inline bool Rect::includes(rect other) const {
    return (other.left >= left) && (other.left <= right) &&
           (other.top >= top) && (other.top <= bottom) &&
           (other.right >= left) && (other.right <= right) &&
           (other.bottom >= top) && (other.bottom <= bottom);
  }

  inline float Rect::width() const { return right - left; }

  inline void Rect::width(float width_) { right = left + width_; }

  inline float Rect::height() const { return (bottom - top); }

  inline void Rect::height(float height_) { bottom = top + height_; }

  inline Point Rect::top_left() const { return {left, top}; }

  inline Point Rect::bottom_right() const { return {right, bottom}; }

  inline Point Rect::top_right() const { return {right, top}; }

  inline Point Rect::bottom_left() const { return {left, bottom}; }

  inline Rect Rect::move(float dx, float dy) const {
    Rect r = *this;
    r.top += dy;
    r.left += dx;
    r.bottom += dy;
    r.right += dx;
    return r;
  }

  inline Rect Rect::move_to(float x, float y) const {
    return move(x - left, y - top);
  }

  inline Rect Rect::inset(float x_inset, float y_inset) const {
    Rect r = *this;
    r.top += y_inset;
    r.left += x_inset;
    r.bottom -= y_inset;
    r.right -= x_inset;

    if (!is_valid(r)) clear(r);

    return r;
  }

  inline bool is_valid(Rect r) {
    return (r.left <= r.right) && (r.top <= r.bottom);
  }

  inline bool is_same_size(Rect a, Rect b) {
    return (a.width() == b.width()) && (a.height() == b.height());
  }

  inline Point center_point(Rect r) {
    return {r.left + (r.width() / 2.0f), r.top + (r.height() / 2.0f)};
  }

  inline float area(Rect r) { return r.width() * r.height(); }

  inline void clear(Rect & r) {
    r.left = 0.0;
    r.top = 0.0;
    r.right = 0.0;
    r.bottom = 0.0;
  }
}

#endif