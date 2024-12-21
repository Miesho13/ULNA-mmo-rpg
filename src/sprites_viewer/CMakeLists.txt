cmake_minimum_required(VERSION 3.22)

project(sprites_viewer)

file(GLOB SPRITE_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

add_executable(${PROJECT_NAME} ${SPRITE_SRC} 
                               ../client/renderer.c 
                               ../client/sprite_data.c
                               ../common/dynamic_array.c)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_BINARY_DIR}/external/raylib/raylib/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../client
    ${CMAKE_CURRENT_SOURCE_DIR}/../common
)

target_link_libraries(${PROJECT_NAME} ${CMAKE_BINARY_DIR}/external/raylib/raylib/libraylib.a m)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/src/sprites_viewer/resources)
