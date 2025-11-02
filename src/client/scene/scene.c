#include "scene.h"

#include <assert.h>


static const scene_t SCENE_ARRAY[SCENE_COUNT] = {
    {
        .name = "LOGIN SCREAN", 
        .id = SCENE_LOGIN 
    },
    {
        .name = "GAME SCENE", 
        .id = SCENE_GAME
    },
    {
        .name = "RENDER TEST",
        .id = SCENE_RENDER_TEST,
    }
};

static scene_t current_scene = SCENE_ARRAY[SCENE_LOGIN];

scene_t scene_get_avaliable_scene_id(scene_id id) {
    return SCENE_ARRAY[id];
}

void scene_set(const scene_id id) {
    current_scene = SCENE_ARRAY[id];
}

scene_t scene_get(void) {
    return current_scene;
}

void scene_show(app_context *app) {
    switch(current_scene.id) {
        case SCENE_LOGIN: { 
            scene_login_screan(app);
            break; 
        }

        case SCENE_GAME: {
            main_scene_step(app);
            break;
        }

        case SCENE_RENDER_TEST: {
            render_test_scene(app);
            break;
        }

        default: { 
            assert(false && "An unnsupported scene was selected");
        }
    }
}

