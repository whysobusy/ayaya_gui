#include "window.h"

#define SK_GL
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "paint/canvas.h"
#include "paint/utils.h"
#include "skia/core/SkCanvas.h"
#include "skia/core/SkColorSpace.h"
#include "skia/core/SkSurface.h"
#include "skia/gpu/GrBackendSurface.h"
#include "skia/gpu/GrDirectContext.h"
#include "skia/gpu/gl/GrGLInterface.h"

// TODO: REFACTOR THE CODE!!!
namespace ayaya {
extern std::map<GLFWwindow*, Window*> windows;

void BeginFrame(GLFWwindow* window) {
  auto wp = static_cast<Window*>(glfwGetWindowUserPointer(window));
  wp->Render();
}

GrDirectContext* sContext = nullptr;
SkSurface* sSurface = nullptr;

void error_callback(int error, const char* description) {
  fputs(description, stderr);
}

void key_callback(GLFWwindow* window,
                  int key,
                  int scancode,
                  int action,
                  int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void init_skia(int w, int h) {
  auto interface = GrGLMakeNativeInterface();
  sContext = GrDirectContext::MakeGL(interface).release();

  GrGLFramebufferInfo framebufferInfo;
  framebufferInfo.fFBOID = 0;  // assume default framebuffer
  // We are always using OpenGL and we use RGBA8 internal format for both RGBA
  // and BGRA configs in OpenGL.
  //(replace line below with this one to enable correct color spaces)
  // framebufferInfo.fFormat = GL_SRGB8_ALPHA8;
  framebufferInfo.fFormat = GL_RGBA8;

  SkColorType colorType = kRGBA_8888_SkColorType;
  GrBackendRenderTarget backendRenderTarget(w, h,
                                            0,  // sample count
                                            0,  // stencil bits
                                            framebufferInfo);

  //(replace line below with this one to enable correct color spaces) sSurface =
  // SkSurface::MakeFromBackendRenderTarget(sContext, backendRenderTarget,
  // kBottomLeft_GrSurfaceOrigin, colorType, SkColorSpace::MakeSRGB(),
  // nullptr).release();
  sSurface = SkSurface::MakeFromBackendRenderTarget(
                 sContext, backendRenderTarget, kBottomLeft_GrSurfaceOrigin,
                 colorType, nullptr, nullptr)
                 .release();
  if (sSurface == nullptr)
    abort();
}

void cleanup_skia() {
  delete sSurface;
  delete sContext;
}

Window::Window(char const* title,
               double width,
               double height,
               Color backGroundColor)
    : backGroundColor_(backGroundColor) {
  window_ = glfwCreateWindow(width, height, title, 0, 0);
  if (window_ == 0) {
    glfwTerminate();
    return;
  }

  glfwSetWindowUserPointer(window_, this);
  glfwSetWindowRefreshCallback(window_, BeginFrame);
  glfwMakeContextCurrent(window_);

  // skia
  init_skia(width, height);
  // skia

  glfwSwapInterval(0);
  glfwSetKeyCallback(window_, key_callback);
  glfwSetTime(0);

  windows[window_] = this;
}

Window::~Window() {
  cleanup_skia();
  windows.erase(window_);
  glfwDestroyWindow(window_);
}

void Window::Draw(Canvas& cnv, int w_width, int w_height) {
  BasicContext bctx{*this, cnv};
  Rect limits = content.Limits(bctx);
  if (limits != currentLimits_) {
    currentLimits_ = limits;
    glfwSetWindowSizeLimits(window_, limits.left, limits.top, limits.right,
                            limits.bottom);
    int w = w_width;
    int h = w_height;
    Clamp(w, limits.left, limits.right);
    Clamp(h, limits.top, limits.bottom);

    if ((w_width != w) || (w_height != h)) {
      glfwSetWindowSize(window_, w, h);
      return;  // return early to refresh/redraw window
    }
  }

  auto size = Size();
  Rect bounds = {0, 0, size.x, size.y};
  Context ctx{*this, cnv, &content, bounds};

  if (bounds != currentBounds_) {
    currentBounds_ = bounds;
    content.Layout(ctx);
  }

  content.Draw(ctx);
}

void Window::Render() {
  double mx, my;
  glfwGetCursorPos(window_, &mx, &my);

  int w_width, w_height;
  glfwGetWindowSize(window_, &w_width, &w_height);

  int fb_width, fb_height;
  glfwGetFramebufferSize(window_, &fb_width, &fb_height);

  // Update and render
  glViewport(0, 0, fb_width, fb_height);
  glClearColor(backGroundColor_.red, backGroundColor_.green,
               backGroundColor_.blue, backGroundColor_.alpha);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  // skia draw
  // SkCanvas* canvas =
  //   sSurface->getCanvas();  // We don't manage this pointer's lifetime.
  // SkPaint paint;
  // paint.setColor(SK_ColorWHITE);
  // canvas->drawPaint(paint);
  // paint.setColor(SK_ColorBLUE);
  // canvas->drawRect({100, 200, 300, 500}, paint);
  // sContext->flush();

  auto draw = [&](auto& _cnv) {
    // TODO scale
    auto cnv = Canvas{_cnv};
    Draw(cnv, w_width, w_height);
  };

  SkCanvas* canvas = sSurface->getCanvas();
  canvas->save();
  draw(canvas);
  canvas->restore();
  sContext->flush();

  glfwSwapBuffers(window_);
}

void Window::Key(KeyInfo const& k) {}

Point Window::CursorPos() const {
  double mx, my;
  glfwGetCursorPos(window_, &mx, &my);
  return {float(mx), float(my)};
}

Point Window::Size() const {
  int width, height;
  glfwGetWindowSize(window_, &width, &height);
  return {float(width), float(height)};
}

void Window::Close() {}
}  // namespace ayaya