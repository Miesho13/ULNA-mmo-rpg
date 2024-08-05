cmake_minimum_required(VERSION 3.28)

project(sprites_viewer)

file(GLOB viewer_sprite "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

add_executable(${PROJECT_NAME} ${viewer_sprite} "${CMAKE_CURRENT_SOURCE_DIR}/../client/resource.c")

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/external/raylib/raylib/include)

target_link_libraries(${PROJECT_NAME} ${CMAKE_BINARY_DIR}/external/raylib/raylib/libraylib.a m)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/src/sprites_viewer/resources)
