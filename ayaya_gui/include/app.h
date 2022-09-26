#pragma once

#include "paint/key.h"

namespace ayaya {
class App {
 public:
  App();
  ~App();
  App(App const&) = delete;
  App& operator=(App const&) = delete;

  virtual void Key(KeyInfo const& k);
  virtual void Run();
};
}  // namespace ayaya