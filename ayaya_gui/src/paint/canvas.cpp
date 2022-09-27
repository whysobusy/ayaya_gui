#include "paint/canvas.h"

#include <stack>

#include <skia/core/SkBitmap.h>
#include <skia/core/SkCanvas.h>
#include <skia/core/SkData.h>
#include <skia/core/SkFont.h>
#include <skia/core/SkImage.h>
#include <skia/core/SkImageFilter.h>
#include <skia/core/SkPath.h>
#include <skia/core/SkPicture.h>
#include <skia/core/SkSurface.h>
#include <skia/core/SkTextBlob.h>
#include <skia/core/SkTypeface.h>
#include <skia/effects/SkGradientShader.h>

namespace ayaya {
class Canvas::CanvasState {
 public:
  struct BlurInfo {
    Point offset_;
    float blur_;
    Color color_;
  };

  CanvasState();

  SkPath& Path();
  SkPaint& FillPaint();
  SkPaint& StrokePaint();
  SkPaint& ClearPaint();

  void Save();
  void Restore();

  float preScale_ = 1.0;

  static SkPaint& GetFillPaint(Canvas const& cnv);

 private:
  struct StateInfo {
    StateInfo() {
      fillPaint_.setAntiAlias(true);
      fillPaint_.setStyle(SkPaint::kFill_Style);
      strokePaint_.setAntiAlias(true);
      strokePaint_.setStyle(SkPaint::kStroke_Style);
    }

    SkPath path_;
    SkPaint fillPaint_;
    SkPaint strokePaint_;
  };

  using StateInfoStack = std::stack<std::unique_ptr<StateInfo>>;

  StateInfo* current() { return stack_.top().get(); }
  StateInfo const* current() const { return stack_.top().get(); }

  StateInfoStack stack_;
  SkPaint clearPaint_;
};

Canvas::CanvasState::CanvasState() {
  stack_.push(std::make_unique<StateInfo>());
  clearPaint_.setAntiAlias(true);
  clearPaint_.setStyle(SkPaint::kFill_Style);
  clearPaint_.setBlendMode(SkBlendMode::kClear);
}

SkPath& Canvas::CanvasState::Path() {
  return current()->path_;
}

SkPaint& Canvas::CanvasState::FillPaint() {
  return current()->fillPaint_;
}

SkPaint& Canvas::CanvasState::StrokePaint() {
  return current()->strokePaint_;
}

SkPaint& Canvas::CanvasState::ClearPaint() {
  return clearPaint_;
}

void Canvas::CanvasState::Save() {
  stack_.push(std::make_unique<StateInfo>(*current()));
}

void Canvas::CanvasState::Restore() {
  if (stack_.size())
    stack_.pop();
}

SkPaint& Canvas::CanvasState::GetFillPaint(Canvas const& cnv) {
  return cnv.state_->FillPaint();
}

Canvas::Canvas(CanvasImpl* context)
    : context_{context}, state_{std::make_unique<CanvasState>()} {}

Canvas::~Canvas() {}

void Canvas::PreScale(float sc) {
  Scale(sc, sc);
  state_->preScale_ = sc;
}

float Canvas::PreScale() const {
  return state_->preScale_;
}

void Canvas::Translate(Point p) {
  context_->translate(p.x, p.y);
}

void Canvas::Rotate(float rad) {
  context_->rotate(rad);
}

void Canvas::Scale(Point p) {
  context_->scale(p.x, p.y);
}

void Canvas::Skew(double sx, double sy) {
  context_->skew(sx, sy);
}

Point Canvas::DeviceToUser(Point p) {
  // TODO
  auto scale = state_->preScale_;
  auto mat = context_->getTotalMatrix();
  (void)mat.invert(&mat);
  SkPoint skp;
  mat.mapXY(p.x * scale, p.y * scale, &skp);
  return {skp.x(), skp.y()};
}

Point Canvas::UserToDevice(Point p) {
  auto scale = state_->preScale_;
  auto mat = context_->getTotalMatrix();
  SkPoint skp;
  mat.mapXY(p.x, p.y, &skp);
  return {skp.x() / scale, skp.y() / scale};
}

void Canvas::Save() {
  context_->save();
  state_->Save();
}

void Canvas::Restore() {
  context_->restore();
  state_->Restore();
}

void Canvas::BeginPath() {
  state_->Path() = {};
}

void Canvas::ClosePath() {
  state_->Path().close();
}

void Canvas::Fill() {
  FillPreserve();
  state_->Path().reset();
}
void Canvas::FillPreserve() {
  context_->drawPath(state_->Path(), state_->FillPaint());
}

void Canvas::Stroke() {
  StrokePreserve();
  state_->Path().reset();
}

void Canvas::StrokePreserve() {
  context_->drawPath(state_->Path(), state_->StrokePaint());
}

void Canvas::Clip() {
  context_->clipPath(state_->Path(), true);
  state_->Path().reset();
}

void Canvas::Clip(Path const& p) {
  // TODO
}

Rect Canvas::ClipContext() const {
  SkRect r;
  context_->getLocalClipBounds(&r);
  return {r.left(), r.top(), r.right(), r.bottom()};
}

void Canvas::MoveTo(Point p) {
  state_->Path().moveTo(p.x, p.y);
}

void Canvas::LineTo(Point p) {
  state_->Path().lineTo(p.x, p.y);
}

void Canvas::MoveTo(float x, float y) {
  state_->Path().moveTo(x, y);
}

void Canvas::LineTo(float x, float y) {
  state_->Path().lineTo(x, y);
}

void Canvas::AddRect(const Rect& r) {
  state_->Path().addRect({r.left, r.top, r.right, r.bottom});
}
void Canvas::AddRectPath(Path const& p) {}

void Canvas::ClearRect(float x, float y, float width, float height) {
  context_->drawRect({x, y, width, height}, state_->ClearPaint());
}

void Canvas::FillStyle(Color c) {
  state_->FillPaint().setColor4f({c.red, c.green, c.blue, c.alpha}, nullptr);
  state_->FillPaint().setShader(nullptr);
}
void Canvas::StrokeStyle(Color c) {
  state_->StrokePaint().setColor4f({c.red, c.green, c.blue, c.alpha}, nullptr);
  state_->StrokePaint().setShader(nullptr);
}
void Canvas::LineWidth(float w) {
  state_->StrokePaint().setStrokeWidth(w);
}
void Canvas::LineCap(Cap _cap) {
  SkPaint::Cap cap = SkPaint::kButt_Cap;
  switch (_cap) {
    case Cap::butt:
      cap = SkPaint::kButt_Cap;
      break;
    case Cap::round:
      cap = SkPaint::kRound_Cap;
      break;
    case Cap::square:
      cap = SkPaint::kSquare_Cap;
      break;
  }
  state_->StrokePaint().setStrokeCap(cap);
}
void Canvas::LineJoin(Join _join) {
  SkPaint::Join join = SkPaint::kMiter_Join;
  switch (_join) {
    case Join::bevel_join:
      join = SkPaint::kBevel_Join;
      break;
    case Join::round_join:
      join = SkPaint::kRound_Join;
      break;
    case Join::miter_join:
      join = SkPaint::kMiter_Join;
      break;
  }
  state_->StrokePaint().setStrokeJoin(join);
}

void Canvas::MiterLimit(float limit) {
  state_->StrokePaint().setStrokeMiter(limit);
}

void Canvas::ShadowStyle(Point offset, float blur, Color c) {
  constexpr auto blur_factor = 0.4f;

  auto matrix = context_->getTotalMatrix();
  auto scx = matrix.getScaleX() / state_->preScale_;
  auto scy = matrix.getScaleY() / state_->preScale_;

  // TODO
}
void Canvas::ShadowStyle(float offsetx, float offsety, float blur, Color c) {
  // TODO
}
void Canvas::ShadowStyle(float blur, Color c) {
  // TODO
}

void Canvas::StrokeColor(Color c) {
  // TODO
}
void Canvas::FillColor(Color c) {
  // TODO
}

void Canvas::GlobalCompositeOperation(CompositeOption mode) {
  SkBlendMode mode_ = SkBlendMode::kSrcOver;
  switch (mode) {
    case source_over:
      mode_ = SkBlendMode::kSrcOver;
      break;
    case source_atop:
      mode_ = SkBlendMode::kSrcATop;
      break;
    case source_in:
      mode_ = SkBlendMode::kSrcIn;
      break;
    case source_out:
      mode_ = SkBlendMode::kSrcOut;
      break;

    case destination_over:
      mode_ = SkBlendMode::kDstOver;
      break;
    case destination_atop:
      mode_ = SkBlendMode::kDstATop;
      break;
    case destination_in:
      mode_ = SkBlendMode::kDstIn;
      break;
    case destination_out:
      mode_ = SkBlendMode::kDstOut;
      break;

    case lighter:
      mode_ = SkBlendMode::kLighten;
      break;
    case darker:
      mode_ = SkBlendMode::kDarken;
      break;
    case copy:
      mode_ = SkBlendMode::kSrc;
      break;
    case xor_:
      mode_ = SkBlendMode::kXor;
      break;

    case difference:
      mode_ = SkBlendMode::kDifference;
      break;
    case exclusion:
      mode_ = SkBlendMode::kExclusion;
      break;
    case multiply:
      mode_ = SkBlendMode::kMultiply;
      break;
    case screen:
      mode_ = SkBlendMode::kScreen;
      break;

    case color_dodge:
      mode_ = SkBlendMode::kColorDodge;
      break;
    case color_burn:
      mode_ = SkBlendMode::kColorBurn;
      break;
    case soft_light:
      mode_ = SkBlendMode::kSoftLight;
      break;
    case hard_light:
      mode_ = SkBlendMode::kHardLight;
      break;

    case hue:
      mode_ = SkBlendMode::kHue;
      break;
    case saturation:
      mode_ = SkBlendMode::kSaturation;
      break;
    case color_op:
      mode_ = SkBlendMode::kColor;
      break;
    case luminosity:
      mode_ = SkBlendMode::kLuminosity;
      break;
  };
  state_->StrokePaint().setBlendMode(mode_);
  state_->FillPaint().setBlendMode(mode_);
}
void Canvas::CompositeOp(CompositeOption mode) {
  // TODO
}

void Canvas::FillStyle(LinearGradient const& gr) {
  // TODO
}
void Canvas::StrokeStyle(LinearGradient const& gr) {
  // TODO
}

void Canvas::FillRect(Rect const& r) {
  // TODO
}
void Canvas::FillRoundRect(Rect const& r, float radius) {
  // TODO
}
void Canvas::StrokeRect(Rect const& r) {
  // TODO
}
void Canvas::StrokeRoundRect(Rect const& r, float radius) {
  // TODO
}

void Canvas::FillRect(float x, float y, float width, float height) {
  // TODO
}
void Canvas::FillRoundRect(float x,
                           float y,
                           float width,
                           float height,
                           float radius) {
  // TODO
}
void Canvas::StrokeRect(float x, float y, float width, float height) {
  // TODO
}
void Canvas::StrokeRoundRect(float x,
                             float y,
                             float width,
                             float height,
                             float radius) {
  // TODO
}
}  // namespace ayaya
