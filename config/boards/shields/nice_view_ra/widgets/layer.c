//
// Created by ricardo on 7/15/2026.
//

#include "layer.h"

void draw_layer_status(lv_obj_t *canvas, const struct status_state *state)
{
    // Draw layer, height=14
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &lv_font_montserrat_14, LV_TEXT_ALIGN_CENTER);

    if (state->layer_label == NULL || strlen(state->layer_label) == 0) {
        char text[10] = {};
        sprintf(text, "LAYER %i", state->layer_index);

        lv_canvas_draw_text(canvas, 0, 0, 68, &label_dsc, text);
    } else {
        lv_canvas_draw_text(canvas, 0, 0, 68, &label_dsc, state->layer_label);
    }
}