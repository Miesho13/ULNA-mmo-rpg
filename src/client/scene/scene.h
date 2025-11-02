#ifndef SCENE_SCENE_H
#define SCENE_SCENE_H

#include "../game.h"

typedef enum {
    SCENE_LOGIN = 0,
    SCENE_GAME,
    SCENE_RENDER_TEST,

    SCENE_COUNT
} scene_id;

typedef struct {
    const char* name;
    scene_id id;
} scene_t;

// SCENE MAIN LOOP
void scene_login_screan(app_context *app);
void main_scene_step(app_context *app);
void render_test_scene(app_context *app);

// SCENE INTERFACE 
void    scene_show(app_context *app);
void    scene_set(const scene_id scene_id);
scene_t scene_get(void);
scene_t scene_get_avaliable_scene_id(scene_id id);




#endif // SCENE_SCENE_H
