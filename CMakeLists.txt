cmake_minimum_required(VERSION 3.28)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(tibia-engine)
set(CMAKE_C_FLAGS "-O0 -Wall -Wextra -Wpedantic -g3")

# ---- client compile ----
add_subdirectory(external/raylib)
include_directories(external/raylib/src)

# ----- common ------
include_directories(src/common)
include_directories(src/server)

add_subdirectory(src/client)
add_subdirectory(src/common)
add_subdirectory(src/server)
add_subdirectory(src/map_edit)

set(CLIENT_NAME ulna-client)
add_executable(${CLIENT_NAME}
    $<TARGET_OBJECTS:client_base>
    $<TARGET_OBJECTS:common>
    $<TARGET_OBJECTS:game_scen_obj>
)

target_link_libraries(
    ${CLIENT_NAME} PUBLIC 
    raylib 
    m
)

# ------ server ------
set(SERVER_NAME ulna-server)
add_executable(${SERVER_NAME}
    $<TARGET_OBJECTS:server_base>
    $<TARGET_OBJECTS:common>
)

# -- mam edit --- 
set(MAP_EDIT map-edit)
add_executable(${MAP_EDIT}
    $<TARGET_OBJECTS:map-edit-obj>
)

target_link_libraries(
    ${MAP_EDIT} PUBLIC 
    raylib 
    m
)

