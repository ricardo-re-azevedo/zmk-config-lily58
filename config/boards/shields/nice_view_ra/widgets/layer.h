//
// Created by ricardo on 7/15/2026.
//

#pragma once

#include <lvgl.h>
#include <zephyr/kernel.h>
#include "util.h"

void draw_layer_status(lv_obj_t *canvas, const struct status_state *state);