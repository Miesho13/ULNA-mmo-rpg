file(GLOB_RECURSE TEST_FILE "*.c")

include_directories(
    ./../src
    ./../src/client
    ./../src/common
    ./../external/raylib/src
)

# add path to addytional .c file
set(ADDYTIONAL_SRC 
    ./../src/common/dynamic_array.c
    ./../src/client/renderer.c
    ./../src/client/sprite_data.c
)

foreach(TEST_FILE ${TEST_FILE})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_FILE} ${ADDYTIONAL_SRC})
    target_link_libraries(${TEST_NAME} PRIVATE ${CMAKE_BINARY_DIR}/external/raylib/raylib/libraylib.a m)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
