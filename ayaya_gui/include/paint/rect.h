#pragma once

#include "paint/point.h"

namespace ayaya {
struct Rect {
  constexpr Rect();
  constexpr Rect(float left, float top, float right, float bottom);
  constexpr Rect(Point top_left, Point bottom_right)
      : Rect(top_left.x, top_left.y, bottom_right.x, bottom_right.y) {}
  Rect(Rect const&) = default;
  Rect& operator=(Rect const&) = default;

  bool operator==(Rect const& other) const;
  bool operator!=(Rect const& other) const;

  bool IsEmpty() const;
  bool Includes(Point const& p) const;
  bool Includes(Rect const& other) const;

  float Width() const;
  void Width(float width_);
  float Height() const;
  void Height(float height_);

  Point TopLeft() const;
  Point BottomRight() const;
  Point TopRight() const;
  Point BottomLeft() const;

  Rect Move(float dx, float dy) const;
  Rect MoveTo(float x, float y) const;
  Rect Inset(float x_inset = 1.0, float y_inset = 1.0) const;

  float top;
  float left;
  float bottom;
  float right;
};

// Utils
bool IsValid(Rect r);
bool IsSameSize(Rect a, Rect b);
bool Intersects(Rect a, Rect b);

Point CenterPoint(Rect r);
float Area(Rect r);
Rect Max(Rect a, Rect b);
Rect Min(Rect a, Rect b);

void Clear(Rect& r);
Rect Center(Rect r, Rect encl);
Rect CenterH(Rect r, Rect encl);
Rect CenterV(Rect r, Rect encl);
Rect Align(Rect r, Rect encl, float x_align, float y_align);
Rect AlignH(Rect r, Rect encl, float x_align);
Rect AlignV(Rect r, Rect encl, float y_align);
Rect Clip(Rect r, Rect encl);

// Inlines
inline constexpr Rect::Rect() : left(0), top(0), right(0), bottom(0) {}

inline constexpr Rect::Rect(float left, float top, float right, float bottom)
    : left(left), top(top), right(right), bottom(bottom) {}

inline bool Rect::operator==(Rect const& other) const {
  return (top == other.top) && (bottom == other.bottom) &&
         (left == other.left) && (right == other.right);
}

inline bool Rect::operator!=(Rect const& other) const {
  return !(*this == other);
}

inline bool Rect::IsEmpty() const {
  return (left == right) || (top == bottom);
}

inline bool Rect::Includes(Point const& p) const {
  return (p.x >= left) && (p.x <= right) && (p.y >= top) && (p.y <= bottom);
}

inline bool Rect::Includes(Rect const& other) const {
  return (other.left >= left) && (other.left <= right) && (other.top >= top) &&
         (other.top <= bottom) && (other.right >= left) &&
         (other.right <= right) && (other.bottom >= top) &&
         (other.bottom <= bottom);
}

inline float Rect::Width() const {
  return right - left;
}

inline void Rect::Width(float width_) {
  right = left + width_;
}

inline float Rect::Height() const {
  return (bottom - top);
}

inline void Rect::Height(float height_) {
  bottom = top + height_;
}

inline Point Rect::TopLeft() const {
  return {left, top};
}

inline Point Rect::BottomRight() const {
  return {right, bottom};
}

inline Point Rect::TopRight() const {
  return {right, top};
}

inline Point Rect::BottomLeft() const {
  return {left, bottom};
}

inline Rect Rect::Move(float dx, float dy) const {
  Rect r = *this;
  r.top += dy;
  r.left += dx;
  r.bottom += dy;
  r.right += dx;
  return r;
}

inline Rect Rect::MoveTo(float x, float y) const {
  return Move(x - left, y - top);
}

inline Rect Rect::Inset(float x_inset, float y_inset) const {
  Rect r = *this;
  r.top += y_inset;
  r.left += x_inset;
  r.bottom -= y_inset;
  r.right -= x_inset;

  if (!IsValid(r))
    Clear(r);

  return r;
}

inline bool IsValid(Rect r) {
  return (r.left <= r.right) && (r.top <= r.bottom);
}

inline bool IsSameSize(Rect a, Rect b) {
  return (a.Width() == b.Width()) && (a.Height() == b.Height());
}

inline Point CenterPoint(Rect r) {
  return {r.left + (r.Width() / 2.0f), r.top + (r.Height() / 2.0f)};
}

inline float Area(Rect r) {
  return r.Width() * r.Height();
}

inline void Clear(Rect& r) {
  r.left = 0.0;
  r.top = 0.0;
  r.right = 0.0;
  r.bottom = 0.0;
}
}  // namespace ayaya