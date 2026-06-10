add_library(GameLib game.c)

target_sources(GameLib
  PRIVATE
  game.c

  PUBLIC FILE_SET HEADERS
  FILES
  game.h
)
