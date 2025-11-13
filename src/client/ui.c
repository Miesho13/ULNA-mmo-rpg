#include "ui.h"
#include "client_config.h"
#include "platform.h"

static const assets_meta_data prv_assets_meta_data[] = {
    // MESSAGE BOX
    {
        .pos_x = 0,
        .pos_y = 0,
        .w = (11*UI_QUANT),
        .h = (6*UI_QUANT),
    },

    //
};

static void ui_msg_box_recipe(ui_context *ctx, void *ui_element) {
    (void)ctx;

    platform_render(
        &((ui_msg_box*)ui_element)->ui_element.sprite, 
        ((ui_msg_box*)ui_element)->ui_element.pos.x, 
        ((ui_msg_box*)ui_element)->ui_element.pos.y, 
        0xFFFFFFFF
    );

    const int width  = ((ui_msg_box*)ui_element)->ui_element.sprite.width;
    const int height = ((ui_msg_box*)ui_element)->ui_element.sprite.height;
    const int font_size = UI_MSG_BOX_DEAFULT_FONT_SIZE*((ui_msg_box*)ui_element)->ui_element.scale;
    const int text_width = platform_mesure_text(
        ((ui_msg_box*)ui_element)->text, 
        UI_MSG_BOX_DEAFULT_FONT_SIZE*((ui_msg_box*)ui_element)->ui_element.scale
    );
    int pos_x  = ((ui_msg_box*)ui_element)->ui_element.pos.x;
    int pos_y  = ((ui_msg_box*)ui_element)->ui_element.pos.y;
    
    pos_x = (pos_x + width - text_width)/2;
    pos_y = (pos_y + height + font_size)/2;

    platform_draw_text(
        ((ui_msg_box*)ui_element)->text, 
        pos_x, pos_y, font_size, 0xB2B2B2FF
    );
}

// TODO: we shoud contain recipe for each context in seperate file
typedef void (*ui_recipe)(ui_context *ctx, void *ui_element);

static ui_recipe call_recipe[] = {
    ui_msg_box_recipe,
};

void ui_load_assets(ui_context *ctx, const char *path) {
    assert(ctx && path && "cant be NULL");
    assert(sizeof(prv_assets_meta_data));

    const platform_img plane = platform_load_img(path);
    const size_t asset_to_load = sizeof(prv_assets_meta_data)/sizeof(prv_assets_meta_data[0]);

    for (size_t asset_id = 0; asset_id < asset_to_load; asset_id++) {
        platform_img    *img = &ctx->asset_img[ctx->asset_count];
        // platform_sprite *sprite = &ctx->asset_gpu[ctx->asset_count];

        const int pos_x = prv_assets_meta_data[asset_id].pos_x;
        const int pos_y = prv_assets_meta_data[asset_id].pos_y;
        const int w = prv_assets_meta_data[asset_id].w;
        const int h = prv_assets_meta_data[asset_id].h;

        *img = platform_load_img_from_image(plane, pos_x, pos_y, w, h);
        // *sprite = platform_load_to_gpu(img);

        ctx->asset_count++;
    }
}

void ui_move_element(ui_context *ui, int id, int pos_x, int pos_y) {
    ui_element *it = ui->render.ui_head;

    while (it->id != id) {
        it = (ui_element*)it->next;
    }

    it->pos.x = pos_x;
    it->pos.y = pos_y;
}

void static ui_element_free(ui_element *element) {
    platform_unload_sprite(&element->sprite);
    free(element);
}

void ui_remove(ui_context *ui, int id) {
    ui_element *it = ui->render.ui_head;
    ui_element *it_next = ((ui_element*)ui->render.ui_head)->next;

    if (it->id == id) {
        ui->render.ui_head = it_next;
        ui_element_free(it);
        return;
    } 

    while (it_next != NULL) {
        if (it_next->id == id) {
            it->next = it_next->next;
            ui_element_free(it_next);
            break;
        }

        it = it_next; 
        it_next = it->next;
    } 

}

int ui_push_msg_box(ui_context *ui, const char *msg, int pos_x, int pos_y, double scale) {
    ui_element *it;

    if (!ui->render.ui_head) {
        it = malloc(sizeof(ui_msg_box));
        ui->render.ui_head = it;
    } 
    else {
        it = ui->render.ui_head;

        while (it->next) {
            it = (ui_element*)it->next;
        }

        it->next = malloc(sizeof(ui_msg_box));
        it = (ui_element*)it->next;
    }

    ui_msg_box *new_el = (ui_msg_box*)it;

    new_el->text = msg;
    new_el->ui_element.id    = ui->render.element_count++;
    new_el->ui_element.type  = UI_MSG_BOX;
    new_el->ui_element.flags = UI_MOVABLE | UI_VISABLE;
    new_el->ui_element.pos.x = pos_x;
    new_el->ui_element.pos.y = pos_y;
    new_el->ui_element.next  = NULL;

    // SCALE IMAGE IF NEEDED
    platform_img img  = platform_img_copy(&ui->asset_img[UI_MSG_BOX]);
    if ((new_el->ui_element.scale = scale) != 1.0) {
        platform_img_resize(
            &img, ui->asset_img[UI_MSG_BOX].width*scale, 
            ui->asset_img[UI_MSG_BOX].height*scale
        ); 
    }

    new_el->ui_element.size.height =  img.height;
    new_el->ui_element.size.width  =  img.width;
    new_el->ui_element.sprite      =  platform_load_to_gpu(&img);

    return new_el->ui_element.id;
}

void ui_render(ui_context *ui) {
    ui_element *it = ui->render.ui_head;

    while (it) {
        if ((it->flags & UI_VISABLE) == UI_VISABLE) {
            call_recipe[it->type](ui, it);
        }
        it = it->next;
    }
}
