#ifndef _EDITOR_GRID_H_
#define _EDITOR_GRID_H_

#define GRID_DRAW_OFFSET 0.01
#define GRID_COLOR vector(128, 128, 128)

int is_grid_visible = true;
int is_layer_1_visible = true;
int is_layer_2_visible = true;
int is_layer_3_visible = true;

array_t *grid_base;
array_t *grid_ceiling;
array_t *grid_obj;

ENTITY *grid_get_base_ent(int index);

ENTITY *grid_get_ceiling_ent(int index);

ENTITY *grid_get_obj_ent(int index);

void grid_get_mouse_pos(int *x, int *y);

int is_pos_on_grid(VECTOR *pos);

int is_allowed_to_draw_map();

void grid_draw(VECTOR *center, var grid_size, int width, int height, COLOR *color);

void grid_ent_fnc();

void grid_initialize();

void grid_clear();

void grid_destroy();

void grid_update();

#endif