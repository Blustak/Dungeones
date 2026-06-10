set(TEST_EXECUTABLE TestMap)
add_executable(${TEST_EXECUTABLE})

target_sources(
  ${TEST_EXECUTABLE}
  PRIVATE
  test_map.c
)

target_link_libraries(
  ${TEST_EXECUTABLE}
  PRIVATE
  GameLib
  raylib
  glfw
)
add_test(NAME "Game lib tests" COMMAND $<TARGET_FILE:${TEST_EXECUTABLE}>)
