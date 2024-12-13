set(LOCAL_NAME "sprite_view");
file(GLOB ${LOCAL_NAME}_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

add_executable(${LOCAL_NAME}.elf %{LOCAL_NAME}_SRC)

target_include_directories(${LOCAL_NAME}.elf PRIVATE ${CMAKE_BINARY_DIR}/external/raylib/raylib/include)

target_link_libraries(${LOCAL_NAME}.elf ${CMAKE_BINARY_DIR}/external/raylib/raylib/libraylib.a m)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/src/sprites_viewer/resources)
