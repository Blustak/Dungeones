#include "game.h"
#include <assert.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_MAP_WIDTH 100
#define TEST_MAP_HEIGHT 100

#define TEST_EMPTY_TILE                                                        \
  (game_tile_t) { .type = EMPTY }
#define TEST_FLOOR_TILE                                                        \
  (game_tile_t) { .type = FLOOR }
#define TEST_WALL_TILE                                                         \
  (game_tile_t) { .type = WALL }

#define TEST_TILES                                                             \
  (game_tile_t *[3]) { &TEST_EMPTY_TILE, &TEST_FLOOR_TILE, &TEST_WALL_TILE }

int main(int argc, char *argv[]) {
  game_map_t map = NewGameMap(TEST_MAP_WIDTH, TEST_MAP_HEIGHT);
  if (map.grid == NULL) {
    fprintf(stderr, "map grid null\n");
    return EXIT_FAILURE;
  }
  for (size_t i = 0; i < map.map_height; i++) {
    if (map.grid[i] == NULL) {
      fprintf(stderr, "map grid row null at %zu.\n", i);
      return EXIT_FAILURE;
    }
  }
  InitWindow(TEST_MAP_WIDTH * 6, TEST_MAP_HEIGHT * 4, "Game lib test");

  // set zero test
  SetTile(&map, TEST_FLOOR_TILE, 0, 0);
  game_tile_t *test_tile = GetTile(&map, 0, 0);

  assert(test_tile == &(map.grid[0][0]));
  assert(test_tile->type == TEST_FLOOR_TILE.type);

  // overwriting
  SetTile(&map, TEST_WALL_TILE, 0, 0);
  test_tile = GetTile(&map, 0, 0);
  assert(test_tile->type == TEST_WALL_TILE.type);

  BeginDrawing();

  assert(DrawTile(GetTile(&map, 0, 0), 10, 10) >= 0);

  EndDrawing();

  FreeGameMap(map);
  return EXIT_SUCCESS;
}
