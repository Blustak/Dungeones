#include "game.h"
#include <assert.h>
#include <raylib.h>
#include <stdlib.h>
#include <string.h>

#define NOT_NULL(p) assert(p != NULL)
#define ASSERT_MAP(map, x, y)                                                  \
  {                                                                            \
    NOT_NULL(map);                                                              \
    assert(x < map->map_width);                                                \
    assert(y < map->map_height);                                               \
  }

game_map_t NewGameMap(unsigned int width, unsigned int height) {
  game_map_t map = {.map_width = width, .map_height = height, .grid = NULL};
  game_tile_t **mapY =
      (game_tile_t **)malloc(sizeof(game_tile_t *) * map.map_height);
  if (mapY == NULL) {
    return map;
  }
  game_tile_t *mapX;
  for (unsigned int i = 0; i < map.map_width; i += 1) {
    mapX = (game_tile_t *)malloc(sizeof(game_tile_t) * map.map_width);
    if (mapX == NULL) {
      map.grid = NULL;
      for (unsigned int j = 0; j < i; j += 1) {
        free(mapY[j]);
      }
      free(mapY);
      return map;
    }
    mapY[i] = mapX;
  }
  map.grid = mapY;
  return map;
}

void FreeGameMap(game_map_t map) {
  for (int i = 0; i < map.map_height; i++) {
    free(map.grid[i]);
  }
  free(map.grid);
}

game_tile_t *GetTile(game_map_t *map, unsigned int x, unsigned int y) {
  ASSERT_MAP(map, x, y);
  return &(map->grid[y][x]);
}

game_tile_t *SetTile(game_map_t *restrict map, game_tile_t tile, unsigned int x,
                     unsigned int y) {
  ASSERT_MAP(map, x, y);
  NOT_NULL(map);
  NOT_NULL(&(map->grid[y][x]));
  map->grid[y][x] = tile;
  return &map->grid[y][x];
}

game_tile_t *SetTiles(game_map_t *restrict map, game_tile_t tile,
                      unsigned int x, unsigned int y, unsigned int width,
                      unsigned int height) {
  ASSERT_MAP(map, x + width, y + height);
  game_tile_t* buf = (game_tile_t*) malloc(sizeof(game_tile_t) * width);
  NOT_NULL(buf);
  for (unsigned int i = 0; i < width; i++) {
    buf[i] = tile;
  }
  for (unsigned int i = y; i < (y + height); i++) {
    memcpy(map->grid[i], buf, sizeof(game_tile_t) * width);
  }
  free(buf);
  return map->grid[y];
}

void MakeRoom(game_map_t *restrict map, unsigned int x1, unsigned int y1,
               unsigned int width, unsigned int height) {
  ASSERT_MAP(map, x1 + width, y1 + height);
  game_tile_t floor = {.type = FLOOR};
  game_tile_t wall = {.type = WALL};
  NOT_NULL(SetTiles(map, wall, x1, y1, width, height));
  x1 += 1, y1 += 1;
  width -=1, height -= 1;
  NOT_NULL(SetTiles(map, floor, x1, y1, width, height));
}

int DrawTile(game_tile_t *tile, int x, int y) {

  Color tileColor;
  switch (tile->type) {
  case EMPTY:
    tileColor = COLOR_TILE_EMPTY;
    break;
  case FLOOR:
    tileColor = COLOR_TILE_FLOOR;
    break;
  case WALL:
    tileColor = COLOR_TILE_WALL;
    break;
  default:
    return -1; // unreachable
  }

  DrawRectangle(x, y, TILE_PIXEL_WIDTH, TILE_PIXEL_HEIGHT, tileColor);
  return 0;
}

int DrawMap(game_map_t *map, unsigned int origin_x, unsigned int origin_y) {
  game_tile_t *tile;
  NOT_NULL(map);
  for (unsigned int y = 0; y < map->map_height; y++) {
    for (unsigned int x = 0; x < map->map_width; x++) {
      tile = &(map->grid[y][x]);
      NOT_NULL(tile);
      int res = DrawTile(tile, origin_x + (TILE_PIXEL_WIDTH * x),
                         origin_y + (TILE_PIXEL_HEIGHT * y));
      if (res != 0) {
        return res;
      }
    }
  }
  return 0;
}
