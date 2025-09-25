#ifndef CLIENT_PLATFORM_H 
#define CLIENT_PLATFORM_H 

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define SPRITE_SHEETS_MAX_COUNT (255) 

void platform_draw_prolog(void);
void platform_draw_epilog(void);
void platform_clear_background(uint32_t color);
void platform_init_window(int width, int height, const char *title, int target_fps);
void platform_load_sprite_sheets(const char **sprite_sheets_path, size_t image_count);                        
bool platform_window_shoud_close(void);
void platform_draw_ractangle(int posX, int posY, int width, int height, uint32_t color);

#endif // CLIENT_PLATFORM_H 
