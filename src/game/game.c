#include "game.h"
#include <raylib.h>
#include <assert.h>
#include <stdlib.h>

game_map_t NewGameMap(unsigned int width, unsigned int height) {
  game_map_t map = {
    .map_width = width,
    .map_height = height,
    .grid = NULL
  };
  game_tile_t** mapY = (game_tile_t**) malloc(sizeof(game_tile_t*) * map.map_height);
  if (mapY == NULL) {
    return map;
  }
  game_tile_t* mapX;
  for (unsigned int i = 0; i < map.map_width; i+=1) {
    mapX = (game_tile_t*)malloc(sizeof(game_tile_t) * map.map_width);
    if (mapX == NULL) {
      map.grid = NULL;
      for(unsigned int j = 0; j < i; j += 1) {
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

void FreeGameMap(game_map_t map){
  for (int i = 0; i < map.map_height; i++) {
    free(map.grid[i]);
  }
  free(map.grid);
}

game_tile_t* GetTile(game_map_t *map, unsigned int x, unsigned int y){
  assert(x < map->map_width && y < map->map_height);
  return &(map->grid[y][x]);
}

game_tile_t* SetTile(game_map_t *map,game_tile_t tile, unsigned int x, unsigned int y){
  assert(x < map->map_width && y < map->map_height);
  game_tile_t* gameTile = GetTile(map, x, y);
  assert(gameTile != NULL);
  *gameTile = tile;
  return gameTile;
}

int DrawTile(game_tile_t *tile, int x, int y){

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
      return -1; //unreachable
  }

  DrawRectangle(x, y, TILE_PIXEL_WIDTH, TILE_PIXEL_HEIGHT, tileColor);
  return 0;
}
