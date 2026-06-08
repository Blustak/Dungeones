#include <raylib.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  InitWindow(200, 200, "Hello, world!");

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Hello, world!", 10, 10, 20, BLACK);
    EndDrawing();
  }
  CloseWindow();
  return EXIT_SUCCESS;
}
