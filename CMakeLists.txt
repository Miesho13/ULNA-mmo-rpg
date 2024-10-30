cmake_minimum_required(VERSION 3.28)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(engine_top_level)

set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -g3")

add_subdirectory(external/raylib)
add_subdirectory(src/client)
add_subdirectory(src/sprites_viewer)

