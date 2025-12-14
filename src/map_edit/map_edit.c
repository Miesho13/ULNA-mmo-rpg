#include "../platform/platform.h"
#include "pick_color.h"
#include "sprite.h"
#include "hit_grid.h"

static struct {
    struct {
        int WIDTH;
        int HEIGHT;
    } window_size;

    sprite_context sprite_ctx; 

    hit_grid hit_grid_ctx;

    struct {
        struct {
            int x;
            int y;
        } mause_pos;


    } input_event;
        

    struct {
        struct {
            int WIDTH;
            int border_margin;

            struct {
                int off_start_x;
                int off_start_y;

                int width;
                int height;

                int item_margin;

            } sprite_picker;

        } right_bar;

        struct {
            int HEIGHT;
            int border_margin;
        } top_bar;

        struct {
            int start_x;
            int start_y;

            int width;
            int height;

        } canvas;

        uint32_t background;
    } ui;

} CORE = {
    .window_size = {
        .WIDTH = 800,
        .HEIGHT = 600,
    },

    .ui = {
        .right_bar = {
            .WIDTH = 300,
            .border_margin = 10,

            .sprite_picker = {
                .off_start_x = 20,
                .off_start_y = 20,
                .width = 280,
                .height = 500,

                .item_margin = 10,
            }
        },

        .top_bar = {
            .HEIGHT = 50,
        },

        .background = WIN_BACKROUND,
    },
};

static inline void input_event(void) 
{
    // current mouse posytion
    CORE.input_event.mause_pos.x = platform_get_mause_x();
    CORE.input_event.mause_pos.y = platform_get_mause_y();

    if (platform_mouse_button_down(PLATFORM_MOUSE_BUTTON_LEFT)) {
        grid_pos pos = hit_grid_pixel_to_cell(
            &CORE.hit_grid_ctx, 
            CORE.input_event.mause_pos.x, 
            CORE.input_event.mause_pos.y
        );

        hit_event *test = hit_grid_get(&CORE.hit_grid_ctx, pos.x, pos.y);
        if (test && test->call) {
            test->call(test);
        }
    }
}

static inline void render_right_background(int start_x, int start_y, int width, int height) 
{
    // render background

    platform_draw_ractangle(
        start_x , start_y, 
        width, 
        height,
        WIN_GRAY_BACKROUND
    );

    platform_draw_line(start_x, start_y, start_x + width, start_y, 2, WIN_TOP_LEFT_BORDER);
    platform_draw_line(start_x, start_y, start_x, start_y + height, 2, WIN_TOP_LEFT_BORDER);
}

void on_click_callback(hit_event *self) 
{
    printf("call id: %d\n", self->value.i32);
}

static inline void render_sprite_picker(int start_x, int start_y, int width, int height) 
{
    const int sprite_w = CORE.sprite_ctx.sprite[0].width;
    const int sprite_h = CORE.sprite_ctx.sprite[0].height;

    const int max_pixel_per_row = CORE.ui.right_bar.WIDTH;
    const int sprite_margin = 16; //CORE.ui.right_bar.sprite_picker.item_margin;

    const int start_x_margin = start_x; // + CORE.ui.right_bar.sprite_picker.off_start_x;
    const int start_y_margin = start_y; // + CORE.ui.right_bar.sprite_picker.off_start_y;

    int pixel_counter = 0;
    int x = 0; int y = 0;
    for (int id = 0; id < 255; ++id) {
        render_sprite(
            &CORE.sprite_ctx, id, 
            start_x_margin + x*(sprite_w + sprite_margin),
            start_y_margin + y*(sprite_h + sprite_margin)
        );

        pixel_counter += sprite_w + sprite_margin;
        x++;
        if ((pixel_counter + sprite_w + CORE.ui.right_bar.sprite_picker.off_start_x) > max_pixel_per_row) {
            pixel_counter = 0;
            x = 0;
            y++;
        }

    }
}

static inline void render_right_bar(void) 
{
    // RENDERER FOR RIGHT BAR
    const int start_x = CORE.window_size.WIDTH - CORE.ui.right_bar.WIDTH; 
    const int start_y = 0;

    const int width  = CORE.ui.right_bar.WIDTH;
    const int height = CORE.window_size.HEIGHT;

    platform_scissor_mode(start_x, start_y, width, height);

    render_right_background(start_x, start_y, width, height);
    render_sprite_picker(start_x, start_y, width, height);

    platform_end_scissor_mode();
}

static inline void render_top_bar_background(int start_x, int start_y, int width, int height) 
{
    // render background

    platform_draw_ractangle(
        start_x , start_y, 
        width, 
        height,
        WIN_GRAY_BACKROUND
    );

    platform_draw_line(start_x, start_y + height, start_x + width, start_y + height, 4, WIN_BOTTOM_RIGHT_BORDER);
}

static inline void render_top_bar(void) 
{
    // RENDERER FOR TOP BAR
    const int start_x = 0;
    const int start_y = 0;

    const int width  = CORE.window_size.WIDTH;
    const int height = CORE.ui.top_bar.HEIGHT;

    platform_scissor_mode(start_x, start_y, width, height);
    render_top_bar_background(start_x, start_y, width, height);

    platform_end_scissor_mode();
}

static inline void render_backlight(void) 
{
    const int mause_x = CORE.input_event.mause_pos.x;
    const int mause_y = CORE.input_event.mause_pos.y;

    grid_pos pos = hit_grid_pixel_to_cell(&CORE.hit_grid_ctx, mause_x, mause_y);
    platform_draw_ractangle(
        pos.x * CORE.hit_grid_ctx.cell_size.width, 
        pos.y * CORE.hit_grid_ctx.cell_size.height, 
        CORE.hit_grid_ctx.cell_size.width, CORE.hit_grid_ctx.cell_size.height, 0xa926b7AA);
}

static inline void render_canvas(void) 
{

}

static inline void render(void) 
{
    // Renders the main user interface elements.
    // This function initializes the drawing, clears the background,
    // and renders the top and right bar components of the UI.
    
    platform_draw_prolog();
    platform_clear_background(CORE.ui.background);

    render_top_bar();
    render_right_bar();
    render_canvas();
    render_backlight();

    platform_draw_epilog();
}

static inline void update_window_event(void) 
{
    CORE.window_size.WIDTH  = platform_get_win_width();
    CORE.window_size.HEIGHT = platform_get_win_height();
}

static inline void hit_gid_service(void)
{

}

void test_button(hit_event *context) 
{
    printf("cell: %d\n", context->value.i32);
}

static inline void polute_grid_on_screan(void) 
{
    int x = 0; int y = 0;

    int idx = 0;
    for (int y = 0; y < 10; ++y) 
    for (int x = 0; x < 10; ++x) {
        hit_event event = {
            .value.i32 = idx++,
            .call = test_button,
            .user_arg = NULL,
        };

        hit_grid_push(&CORE.hit_grid_ctx, x, y, event);
    }
}

void map_edit_init(void) 
{
    platform_init_window(CORE.window_size.WIDTH, CORE.window_size.HEIGHT, "ulma-map-edit", 144);
    load_sprite(&CORE.sprite_ctx);
    hit_grid_init(&CORE.hit_grid_ctx, 16, 16);
    // polute_grid_on_screan();
}

void map_edit_run(void) 
{
    while (!platform_window_shoud_close()) {
        update_window_event();
        input_event();
        render();
    }
}
