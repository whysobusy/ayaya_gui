// ayaya_gui.cpp : Defines the entry point for the application.
//

#include "app.h"
#include "window.h"

int main() {
  ayaya::App my_app;
  ayaya::Window window("ayaya", 1000, 600, ayaya::Color::Blue());
  my_app.Run();
}
