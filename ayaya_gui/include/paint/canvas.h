#pragma once

#include "color.h"
#include "path.h"
#include "point.h"
#include "rect.h"

#include <memory>
#include <vector>

class SkCanvas;

namespace ayaya {
using CanvasImpl = SkCanvas;

class Canvas {
 public:
  explicit Canvas(CanvasImpl* context_);
  Canvas(Canvas const& rhs) = delete;
  ~Canvas();

  Canvas(Canvas&& rhs) = delete;
  Canvas& operator=(Canvas const& rhs) = delete;
  CanvasImpl* Impl() const;

  void PreScale(float sc);
  float PreScale() const;

  // Transform
  void Translate(Point p);
  void Translate(float x, float y);
  void Rotate(float rad);
  void Scale(Point p);
  void Scale(float x, float y);
  void Skew(double sx, double sy);
  Point DeviceToUser(Point p);
  Rect DeviceToUser(Rect rect);
  Point UserToDevice(Point p);

  // Paths
  void BeginPath();
  void ClosePath();
  void Fill();
  void FillPreserve();
  void Stroke();
  void StrokePreserve();

  void Clip();
  void Clip(Path const& p);
  Rect ClipContext() const;

  void MoveTo(Point p);
  void LineTo(Point p);
  void MoveTo(float x, float y);
  void LineTo(float x, float y);
  void AddRect(const Rect& r);
  void AddRectPath(Path const& p);
  void ClearRect(float x, float y, float width, float height);

  enum Cap {
    butt,
    round,
    square,
  };

  enum Join {
    bevel_join,
    round_join,
    miter_join,
  };

  void FillStyle(Color c);
  void StrokeStyle(Color c);
  void LineWidth(float w);
  void LineCap(Cap cap);
  void LineJoin(Join join);
  void MiterLimit(float limit = 10);
  void ShadowStyle(Point offset, float blur, Color c);
  void ShadowStyle(float offsetx, float offsety, float blur, Color c);
  void ShadowStyle(float blur, Color c);

  void StrokeColor(Color c);
  void FillColor(Color c);

  enum CompositeOption {
    source_over,
    source_atop,
    source_in,
    source_out,

    destination_over,
    destination_atop,
    destination_in,
    destination_out,

    lighter,
    darker,
    copy,
    xor_,

    difference,
    exclusion,
    multiply,
    screen,

    color_dodge,
    color_burn,
    soft_light,
    hard_light,

    hue,
    saturation,
    color_op,
    luminosity,
  };

  void GlobalCompositeOperation(CompositeOption mode);
  void CompositeOp(CompositeOption mode);

  struct ColorStop {
    float offset;
    struct Color color;
  };

  struct Gradient {
    void AddColorStop(ColorStop cs);
    void AddColorStop(float offset, struct Color color_);
    std::vector<ColorStop> color_space = {};
  };

  // TODO
  struct LinearGradient : Gradient {
    LinearGradient(float startx, float starty, float endx, float endy)
        : start{startx, starty}, end{endx, endy} {}

    LinearGradient(Point start, Point end) : start{start}, end{end} {}

    Point start = {};
    Point end = {};
  };

  void FillStyle(LinearGradient const& gr);
  void StrokeStyle(LinearGradient const& gr);

  // Rect
  void FillRect(Rect const& r);
  void FillRoundRect(Rect const& r, float radius);
  void StrokeRect(Rect const& r);
  void StrokeRoundRect(Rect const& r, float radius);

  void FillRect(float x, float y, float width, float height);
  void FillRoundRect(float x, float y, float width, float height, float radius);
  void StrokeRect(float x, float y, float width, float height);
  void StrokeRoundRect(float x,
                       float y,
                       float width,
                       float height,
                       float radius);

  class State {
   public:
    State(Canvas& cnv_);
    State(State&& rhs) noexcept;
    State(State const&) = delete;
    ~State();

    State& operator=(State const&) = delete;
    State& operator=(State&& rhs) noexcept;

   private:
    Canvas* cnv;
  };

  State new_state() { return State{*this}; }
  void Save();
  void Restore();

  class CanvasState;

 private:
  CanvasImpl* context_;
  std::unique_ptr<CanvasState> state_;
};
}  // namespace ayaya