cmake_minimum_required(VERSION 3.28)

add_library(client_base OBJECT 
    main.c
    game.c 
    platform.c
    client.c
    renderer.c 
    tile.c
)

add_library(game_scen_obj OBJECT 
    scene/main_scene.c
    scene/login_screan.c
    scene/scene.c
    scene/render_test_scene.c
)

