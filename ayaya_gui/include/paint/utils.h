#pragma once

#include <cassert>
#include "paint/rect.h"

namespace ayaya {
constexpr float fullExtent = 1E6;
constexpr Rect fullLimit = {0.0, 0.0, fullExtent, fullExtent};
constexpr Rect EmptyLimit = {0.0, 0.0, 0.0, 0.0};
constexpr Rect EmptyRect = {0.0, 0.0, 0.0, 0.0};

template <typename T, typename U>
inline void ClampMax(T& val, U& const max) {
  if (val > max) {
    val = max;
  }
}

template <typename T, typename U>
inline void ClampMin(T& val, U& const min) {
  if (val < min) {
    val = min;
  }
}

template <typename T, typename U, typename V>
inline void Clamp(T& val, U& const min, U& const max) {
  assert(min <= max);
  ClampMin(val, min);
  ClampMax(val, max);
}

template <typename T, typename U, typename V>
inline bool Within(T const& val, U const& min, V const& max) {
  return (val >= min) && (val <= max);
}
}  // namespace ayaya