#include "game.h"
#include <assert.h>
#include <stdlib.h>

game_map_t NewGameMap(unsigned int width, unsigned int height) {
  game_map_t map = {
    .map_width = width,
    .map_height = height,
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
  return map;
}

game_tile_t* GetTile(game_map_t *map, unsigned int x, unsigned int y){
  if (x >= map->map_width || y >= map->map_height) {
    return NULL; // Error oob
  }
  return &(map->grid[y][x]);
}

int SetTile(game_map_t *map, unsigned int x, unsigned int y){
  assert(x < map->map_width && y < map->map_height);
}
