// ayaya_gui.cpp : Defines the entry point for the application.
//

#include "app.h"
#include "widget/basic.h"
#include "widget/widget.h"
#include "window.h"

int main() {
  ayaya::App my_app;
  ayaya::Window window("ayaya", 1000, 600, ayaya::Color::Blue());
  ayaya::WidgetPtr mainWidget;

  window.content.elements.push_back(New_(ayaya::Panel{}));
  my_app.Run();
}
