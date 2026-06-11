#pragma once
#include <stddef.h>
#include <raylib.h>
#define TILE_PIXEL_WIDTH 10
#define TILE_PIXEL_HEIGHT 16

#define COLOR_TILE_EMPTY (Color)BLACK
#define COLOR_TILE_FLOOR (Color)YELLOW
#define COLOR_TILE_WALL (Color)RAYWHITE

typedef enum{
  EMPTY,
  FLOOR,
  WALL
} tile_type_t;

typedef struct GameTile{
  tile_type_t type;
} game_tile_t;

typedef struct GameMap{
  unsigned int map_width;
  unsigned int map_height;
  game_tile_t** grid;
} game_map_t;

game_map_t NewGameMap(unsigned int width, unsigned int height);
game_tile_t* GetTile(game_map_t* map, unsigned int x, unsigned int y);
game_tile_t* SetTile(game_map_t* map, game_tile_t tile, unsigned int x, unsigned int y);

int DrawTile(game_tile_t* tile, int x, int y);
int DrawMap(game_map_t* map, unsigned int x, unsigned int y);
void FreeGameMap(game_map_t map);
