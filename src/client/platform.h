#ifndef CLIENT_PLATFORM_H 
#define CLIENT_PLATFORM_H 

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <common.h>

#define SPRITE_SHEETS_MAX_COUNT (255) 

typedef enum {
    PLATFORM_KEY_NULL            = 0,        // Key: NULL, used for no key pressed
    // Alphanumeric keys
    PLATFORM_KEY_APOSTROPHE      = 39,       // Key: '
    PLATFORM_KEY_COMMA           = 44,       // Key: ,
    PLATFORM_KEY_MINUS           = 45,       // Key: -
    PLATFORM_KEY_PERIOD          = 46,       // Key: .
    PLATFORM_KEY_SLASH           = 47,       // Key: /
    PLATFORM_KEY_ZERO            = 48,       // Key: 0
    PLATFORM_KEY_ONE             = 49,       // Key: 1
    PLATFORM_KEY_TWO             = 50,       // Key: 2
    PLATFORM_KEY_THREE           = 51,       // Key: 3
    PLATFORM_KEY_FOUR            = 52,       // Key: 4
    PLATFORM_KEY_FIVE            = 53,       // Key: 5
    PLATFORM_KEY_SIX             = 54,       // Key: 6
    PLATFORM_KEY_SEVEN           = 55,       // Key: 7
    PLATFORM_KEY_EIGHT           = 56,       // Key: 8
    PLATFORM_KEY_NINE            = 57,       // Key: 9
    PLATFORM_KEY_SEMICOLON       = 59,       // Key: ;
    PLATFORM_KEY_EQUAL           = 61,       // Key: =
    PLATFORM_KEY_A               = 65,       // Key: A | a
    PLATFORM_KEY_B               = 66,       // Key: B | b
    PLATFORM_KEY_C               = 67,       // Key: C | c
    PLATFORM_KEY_D               = 68,       // Key: D | d
    PLATFORM_KEY_E               = 69,       // Key: E | e
    PLATFORM_KEY_F               = 70,       // Key: F | f
    PLATFORM_KEY_G               = 71,       // Key: G | g
    PLATFORM_KEY_H               = 72,       // Key: H | h
    PLATFORM_KEY_I               = 73,       // Key: I | i
    PLATFORM_KEY_J               = 74,       // Key: J | j
    PLATFORM_KEY_K               = 75,       // Key: K | k
    PLATFORM_KEY_L               = 76,       // Key: L | l
    PLATFORM_KEY_M               = 77,       // Key: M | m
    PLATFORM_KEY_N               = 78,       // Key: N | n
    PLATFORM_KEY_O               = 79,       // Key: O | o
    PLATFORM_KEY_P               = 80,       // Key: P | p
    PLATFORM_KEY_Q               = 81,       // Key: Q | q
    PLATFORM_KEY_R               = 82,       // Key: R | r
    PLATFORM_KEY_S               = 83,       // Key: S | s
    PLATFORM_KEY_T               = 84,       // Key: T | t
    PLATFORM_KEY_U               = 85,       // Key: U | u
    PLATFORM_KEY_V               = 86,       // Key: V | v
    PLATFORM_KEY_W               = 87,       // Key: W | w
    PLATFORM_KEY_X               = 88,       // Key: X | x
    PLATFORM_KEY_Y               = 89,       // Key: Y | y
    PLATFORM_KEY_Z               = 90,       // Key: Z | z
    PLATFORM_KEY_LEFT_BRACKET    = 91,       // Key: [
    PLATFORM_KEY_BACKSLASH       = 92,       // Key: '\'
    PLATFORM_KEY_RIGHT_BRACKET   = 93,       // Key: ]
    PLATFORM_KEY_GRAVE           = 96,       // Key: `
    // Function keys
    PLATFORM_KEY_SPACE           = 32,       // Key: Space
    PLATFORM_KEY_ESCAPE          = 256,      // Key: Esc
    PLATFORM_KEY_ENTER           = 257,      // Key: Enter
    PLATFORM_KEY_TAB             = 258,      // Key: Tab
    PLATFORM_KEY_BACKSPACE       = 259,      // Key: Backspace
    PLATFORM_KEY_INSERT          = 260,      // Key: Ins
    PLATFORM_KEY_DELETE          = 261,      // Key: Del
    PLATFORM_KEY_RIGHT           = 262,      // Key: Cursor right
    PLATFORM_KEY_LEFT            = 263,      // Key: Cursor left
    PLATFORM_KEY_DOWN            = 264,      // Key: Cursor down
    PLATFORM_KEY_UP              = 265,      // Key: Cursor up
    PLATFORM_KEY_PAGE_UP         = 266,      // Key: Page up
    PLATFORM_KEY_PAGE_DOWN       = 267,      // Key: Page down
    PLATFORM_KEY_HOME            = 268,      // Key: Home
    PLATFORM_KEY_END             = 269,      // Key: End
    PLATFORM_KEY_CAPS_LOCK       = 280,      // Key: Caps lock
    PLATFORM_KEY_SCROLL_LOCK     = 281,      // Key: Scroll down
    PLATFORM_KEY_NUM_LOCK        = 282,      // Key: Num lock
    PLATFORM_KEY_PRINT_SCREEN    = 283,      // Key: Print screen
    PLATFORM_KEY_PAUSE           = 284,      // Key: Pause
    PLATFORM_KEY_F1              = 290,      // Key: F1
    PLATFORM_KEY_F2              = 291,      // Key: F2
    PLATFORM_KEY_F3              = 292,      // Key: F3
    PLATFORM_KEY_F4              = 293,      // Key: F4
    PLATFORM_KEY_F5              = 294,      // Key: F5
    PLATFORM_KEY_F6              = 295,      // Key: F6
    PLATFORM_KEY_F7              = 296,      // Key: F7
    PLATFORM_KEY_F8              = 297,      // Key: F8
    PLATFORM_KEY_F9              = 298,      // Key: F9
    PLATFORM_KEY_F10             = 299,      // Key: F10
    PLATFORM_KEY_F11             = 300,      // Key: F11
    PLATFORM_KEY_F12             = 301,      // Key: F12
    PLATFORM_KEY_LEFT_SHIFT      = 340,      // Key: Shift left
    PLATFORM_KEY_LEFT_CONTROL    = 341,      // Key: Control left
    PLATFORM_KEY_LEFT_ALT        = 342,      // Key: Alt left
    PLATFORM_KEY_LEFT_SUPER      = 343,      // Key: Super left
    PLATFORM_KEY_RIGHT_SHIFT     = 344,      // Key: Shift right
    PLATFORM_KEY_RIGHT_CONTROL   = 345,      // Key: Control right
    PLATFORM_KEY_RIGHT_ALT       = 346,      // Key: Alt right
    PLATFORM_KEY_RIGHT_SUPER     = 347,      // Key: Super right
    PLATFORM_KEY_KB_MENU         = 348,      // Key: KB menu
    // Keypad keys
    PLATFORM_KEY_KP_0            = 320,      // Key: Keypad 0
    PLATFORM_KEY_KP_1            = 321,      // Key: Keypad 1
    PLATFORM_KEY_KP_2            = 322,      // Key: Keypad 2
    PLATFORM_KEY_KP_3            = 323,      // Key: Keypad 3
    PLATFORM_KEY_KP_4            = 324,      // Key: Keypad 4
    PLATFORM_KEY_KP_5            = 325,      // Key: Keypad 5
    PLATFORM_KEY_KP_6            = 326,      // Key: Keypad 6
    PLATFORM_KEY_KP_7            = 327,      // Key: Keypad 7
    PLATFORM_KEY_KP_8            = 328,      // Key: Keypad 8
    PLATFORM_KEY_KP_9            = 329,      // Key: Keypad 9
    PLATFORM_KEY_KP_DECIMAL      = 330,      // Key: Keypad .
    PLATFORM_KEY_KP_DIVIDE       = 331,      // Key: Keypad /
    PLATFORM_KEY_KP_MULTIPLY     = 332,      // Key: Keypad *
    PLATFORM_KEY_KP_SUBTRACT     = 333,      // Key: Keypad -
    PLATFORM_KEY_KP_ADD          = 334,      // Key: Keypad +
    PLATFORM_KEY_KP_ENTER        = 335,      // Key: Keypad Enter
    PLATFORM_KEY_KP_EQUAL        = 336,      // Key: Keypad =
} keyboard_key;

typedef enum {
    PLATFORM_MOUSE_BUTTON_LEFT    = 0,
    PLATFORM_MOUSE_BUTTON_RIGHT   = 1,
    PLATFORM_MOUSE_BUTTON_MIDDLE  = 2,
    PLATFORM_MOUSE_BUTTON_SIDE    = 3,
    PLATFORM_MOUSE_BUTTON_EXTRA   = 4,
    PLATFORM_MOUSE_BUTTON_FORWARD = 5,
    PLATFORM_MOUSE_BUTTON_BACK    = 6,
} mouse_button_t;

void platform_draw_prolog(void);
void platform_draw_epilog(void);
void platform_clear_background(uint32_t color);
void platform_init_window(int width, int height, const char *title, int target_fps);
void platform_load_sprite_sheets(const char **sprite_sheets_path, size_t image_count);                        
bool platform_window_shoud_close(void);
void platform_draw_ractangle(int posX, int posY, int width, int height, uint32_t color);
void platform_draw_text(const char *text, int posX, int posY, int fontSize, uint32_t color);                

// INPUT HANDLE
bool platform_key_press(keyboard_key key);
bool platform_key_down(keyboard_key key);
bool platform_key_relased(keyboard_key key);
bool platform_key_up(keyboard_key key);
bool platform_key_pressed_pepeat(keyboard_key key);

// Mause input

bool platform_mouse_button_pressed(int button);
bool platform_mouse_button_down(int button);
bool platform_mouse_button_released(int button);
bool platform_mouse_button_up(int button);
int platform_get_mause_x(void);
int platform_get_mause_y(void);
v2_i32 platform_get_mause(void);

// Time


#endif // CLIENT_PLATFORM_H 
