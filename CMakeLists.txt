cmake_minimum_required(VERSION 4.0.0)

set(CMAKE_C_COMPILER "/usr/bin/clang")
project(Dungeones2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)

option(BUILD_TESTS "Enable building of test executables" ON)

set(RAYLIB_VERSION 6.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)

if (NOT raylib_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
  endif()
endif()

add_executable(${PROJECT_NAME})
add_subdirectory("./src")

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

target_include_directories(
  ${PROJECT_NAME} PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/include"
)
target_link_libraries(${PROJECT_NAME} PUBLIC GameLib raylib)
