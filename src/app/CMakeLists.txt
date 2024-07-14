cmake_minimum_required(VERSION 3.28)

project(application_tibia)

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/libraylib.a m)


