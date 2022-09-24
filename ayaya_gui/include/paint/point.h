ifndef AYAYA
#define AYAYA

namespace Ayaya {
  struct Point {
    constexpr Point();
    constexpr Point(float x, float y);
    Point& operator=(Point const other) = default;

    bool operator==(Point const& other) const;
    bool operator!=(Point const& other) const;

    Point Move(float dx, float dy) const;
    Point MoveTo(float x, float y) const;

    float x;
    float y;
  };

  //Inlines
  inline constexpr Point::Point() : x(0.0), y(0.0) {}

  inline constexpr Point::Point(float x, float y) : x(x), y(y) {}

  inline bool Point::operator==(Point const& other) const {
    return (other.x == x) && (other.y == y);
  }

  inline bool Point::operator!=(Point const& other) const {
    return !(*this == other);
  }

  inline Point Point::Move(float dx, float dy) const {
    Point r = *this;
    r.x += dx;
    r.y += dy;
    return r;
  }

  inline Point Point::MoveTo(float x_, float y_) const {
    Point r = *this;
    r.x = x_;
    r.y = y_;
    return r;
  }
}

#endif