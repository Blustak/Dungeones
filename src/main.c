#include <raylib.h>
#include "defs.h"

int main(int argc, char *argv[])
{
  const int screen_width = SCREEN_WIDTH;
  const int screen_height = SCREEN_HEIGHT;

  InitWindow(screen_width, screen_height, "Hello world example");

  while (!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Hello, world!", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 12, BLUE);

    EndDrawing();
  }
  CloseWindow();
  return 0;
}
