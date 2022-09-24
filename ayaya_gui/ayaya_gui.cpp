// ayaya_gui.cpp : Defines the entry point for the application.
//

#include "ayaya_gui.h"

#include <GLFW/glfw3.h>

#include "skia/core/SkCanvas.h"
#include "skia/core/SkData.h"
#include "skia/core/SkImage.h"
#include "skia/core/SkPaint.h"
#include "skia/core/SkPath.h"
#include "skia/core/SkStream.h"
#include "skia/core/SkSurface.h"

void draw(SkCanvas* canvas);

int main() {
  sk_sp<SkSurface> surface;
  SkCanvas* canvas;

  surface = SkSurface::MakeRasterN32Premul(100, 100);
  canvas = surface->getCanvas();

  // draw(canvas);

  sk_sp<SkImage> img(surface->makeImageSnapshot());
  sk_sp<SkData> png(img->encodeToData());
  SkFILEWStream out("output.png");
  out.write(png->data(), png->size());
}

void draw(SkCanvas* canvas) {
  canvas->save();
  canvas->translate(SkIntToScalar(128), SkIntToScalar(128));
  canvas->rotate(SkIntToScalar(45));
  SkRect rect = SkRect::MakeXYWH(-90.5f, -90.5f, 181.0f, 181.0f);
  SkPaint paint;
  paint.setColor(SK_ColorBLUE);
  canvas->drawRect(rect, paint);
  canvas->restore();
}