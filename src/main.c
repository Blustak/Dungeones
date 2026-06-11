#include <raylib.h>
#include <stdlib.h>
#include "game.h"


int main(int argc, char *argv[])
{
  game_map_t map = NewGameMap(100, 100);
  game_tile_t wall = {
    .type = WALL
  };
  for (int i = 0; i < 5; i++){
    for(int j = 0; j < 7; j++) {
      SetTile(&map, wall, j, i);
    }
  }
  game_tile_t floor = {
    .type = FLOOR,
  };
  size_t counter = 0;
  InitWindow(800, 800, "Map test");

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if(counter == 60) {
      SetTile(&map, floor, 20, 20);
    }
    if (counter == 680) {
      SetTile(&map, wall, 21,21);
      counter = 0;
    }
    DrawMap(&map, 5, 5);
    EndDrawing();
    counter += 1;
  }
  CloseWindow();
  return EXIT_SUCCESS;
}
