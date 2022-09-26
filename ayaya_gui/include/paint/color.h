#pragma once

namespace ayaya {
struct Color {
  static constexpr Color Red() { return Color(255, 0, 0); }
  static constexpr Color Green() { return Color(0, 255, 0); }
  static constexpr Color Blue() { return Color(0, 0, 255); }
  static constexpr Color Black() { return Color(0, 0, 0); }
  static constexpr Color White() { return Color(255, 255, 255); }

  constexpr Color() = default;
  constexpr Color::Color(float red, float green, float blue, float alpha = 255)
      : red(red), green(green), blue(blue), alpha(alpha) {}

  float red = 0.0f;
  float green = 0.0f;
  float blue = 0.0f;
  float alpha = 0.0f;
};

bool operator==(Color& a, Color& b);
bool operator!=(Color& a, Color& b);

// Inlines
inline bool operator==(Color const& a, Color const& b) {
  return (a.alpha == b.alpha) && (a.red == b.red) && (a.green == b.green) &&
         (a.blue == b.blue);
}

inline bool operator!=(Color const& a, Color const& b) {
  return !(a == b);
}
}  // namespace ayaya
