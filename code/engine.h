#ifndef _ENGINE_H_
#define _ENGINE_H_

BMAP *mouse_tga = "mouse.tga";

var autolock_mouse_locked = false;

float get_hsv_from_color(float value);

float get_color_from_hsv(float value);

void change_color_from_hsv(COLOR *color, float color_red, float color_green, float color_blue);

void mouse_set_position(VECTOR *pos);

VECTOR *mouse_get_position();

void mouse_set_map(BMAP *new_mouse_map);

void mouse_enable(var is_mouse_centered);

void mouse_disable();

void mouse_lock_in_window();

void engine_set_resolution_from_id(var id, var display_mode);

void engine_apply_video_settings();

void engine_initialize();

#endif