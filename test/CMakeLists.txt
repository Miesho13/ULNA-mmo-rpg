cmake_minimum_required(VERSION 3.28)

project(engine_top_level)

set(SRC_MAIN_APP ./src/main.c)

add_executable(${PROJECT_NAME} ${SRC_MAIN_APP})

target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/lib/libraylib.a m)

