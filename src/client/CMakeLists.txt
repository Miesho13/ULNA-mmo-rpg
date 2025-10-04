cmake_minimum_required(VERSION 3.28)

add_library(client_base OBJECT 
    main.c
    game.c 
    platform.c
    client.c
    time_bench.c
)

add_library(game_scen_obj OBJECT 
    scene/main_scene.c
)

