#ifndef CLIENT_GAME_H
#define CLIENT_GAME_H

#include <stdint.h> 
#include <stdbool.h> 

typedef struct {
    int window_width;
    int window_height;
    
    struct {
        uint16_t id;
        bool login;
    } client_context;

    bool game_close;
} app_context;


// general
void close_game(void);
void game_init(void);
int  game_run(void);


#endif
