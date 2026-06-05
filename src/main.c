#include <raylib.h>
#include "defs.h"
#include "display_driver.h"

int main(int argc, char *argv[])
{
  const int screen_width = SCREEN_WIDTH;
  const int screen_height = SCREEN_HEIGHT;
  display_driver_t* display_driver = NewDisplayDriver();
  const draw_rect_t simpleRect = {.start_pos = {.x = 10,.y = 10},
    .width = 50,
    .height = 100,
    .color = GREEN
  };
  drawable_t simpleLine = {
    .v_line = {
      .start_pos = {.x = 10, .y = 10},
      .end_pos = {.x = SCREEN_WIDTH - 10, .y = SCREEN_HEIGHT - 20},
      .color = RED
    }
  };
  drawable_t simpleDrawableRect = {
    .v_rect = simpleRect,
  };


  InitWindow(screen_width, screen_height, "Hello world example");

  while (!WindowShouldClose()){
    PushToStack(display_driver, &simpleDrawableRect, RECT);
    PushToStack(display_driver, &simpleLine, LINE);
    FlushDrawStack(display_driver);
  }
  CloseWindow();
  FreeDisplayDriver(display_driver);
  return 0;
}
