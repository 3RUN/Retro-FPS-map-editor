
void game_build_map_initialize()
{
    vec_set(&cardinal_dir[TOP], vector(0, -1, 0));   // top
    vec_set(&cardinal_dir[RIGHT], vector(1, 0, 0));  // right
    vec_set(&cardinal_dir[BOTTOM], vector(0, 1, 0)); // bottom
    vec_set(&cardinal_dir[LEFT], vector(-1, 0, 0));  // left

    cardinal_rot[TOP] = 270;   // top
    cardinal_rot[RIGHT] = 180; // right
    cardinal_rot[BOTTOM] = 90; // bottom
    cardinal_rot[LEFT] = 0;    // left

    // create materials
    mtl_solid = mtl_create();
    effect_load(mtl_solid, "mtl_solid.fx");

    mtl_two_sided = mtl_create();
    effect_load(mtl_two_sided, "mtl_two_sided.fx");

    map_solid = array_create(ENTITY *, 1);
    map_props = array_create(ENTITY *, 1);
    map_events = array_create(ENTITY *, 1);
    map_items = array_create(ENTITY *, 1);
    map_enemies = array_create(ENTITY *, 1);
    map_bosses = array_create(ENTITY *, 1);
}

void game_build_free_array(array_t *array)
{
    if (!array)
    {
        return;
    }

    array_enumerate_begin(ENTITY *, array, v)
    {
        if (v)
        {
            safe_remove(v);
        }
    }
    array_enumerate_end(array);
}

void game_build_destroy_array(array_t *array)
{
    if (!array)
    {
        return;
    }

    game_build_free_array(array);
    array_destroy(array);
}

void game_build_map_free()
{
    if (map_ceiling_ent)
    {
        safe_remove(map_ceiling_ent);
    }

    if (map_floor_ent)
    {
        safe_remove(map_floor_ent);
    }

    game_build_free_array(map_solid);
    game_build_free_array(map_props);
    game_build_free_array(map_events);
    game_build_free_array(map_items);
    game_build_free_array(map_enemies);
    game_build_free_array(map_bosses);
}

void game_build_map_destroy()
{
    if (mtl_solid)
    {
        effect_load(mtl_solid, NULL);
        ptr_remove(mtl_solid);
    }

    if (mtl_two_sided)
    {
        effect_load(mtl_two_sided, NULL);
        ptr_remove(mtl_two_sided);
    }

    if (map_ceiling_ent)
    {
        safe_remove(map_ceiling_ent);
    }

    if (map_floor_ent)
    {
        safe_remove(map_floor_ent);
    }

    game_build_destroy_array(map_solid);
    game_build_destroy_array(map_props);
    game_build_destroy_array(map_events);
    game_build_destroy_array(map_items);
    game_build_destroy_array(map_enemies);
    game_build_destroy_array(map_bosses);
}

int game_build_check_direction(Map *map, VECTOR *pos, VECTOR *dir)
{
    if (!map)
    {
        return false;
    }

    VECTOR endpos, tempdir;

    vec_set(&tempdir, dir);
    vec_set(&endpos, pos);
    vec_add(&endpos, &tempdir);

    if (endpos.x < 0 || endpos.x >= MAP_WIDTH || endpos.y < 0 || endpos.y >= MAP_HEIGHT)
    {
        return false;
    }

    int x = endpos.x;
    int y = endpos.y;

    return map->cell[x][y].type != ASSET_TYPE_WALLS;
}

int is_neighbour_is_door(Map *map, VECTOR *pos, VECTOR *dir)
{
    if (!map)
    {
        return false;
    }

    VECTOR endpos, tempdir;

    vec_set(&tempdir, dir);
    vec_set(&endpos, pos);
    vec_add(&endpos, &tempdir);

    if (endpos.x < 0 || endpos.x >= MAP_WIDTH || endpos.y < 0 || endpos.y >= MAP_HEIGHT)
    {
        return false;
    }

    int x = endpos.x;
    int y = endpos.y;

    int type = map->cell[x][y].type;
    int asset = map->cell[x][y].asset;

    return is_a_door(type, asset);
}

int is_a_door(int type, int asset)
{
    if (type != ASSET_TYPE_PROPS)
    {
        return false;
    }

    if (asset != PROPS_DOOR && asset != PROPS_DOOR_ELEVATOR && asset != PROPS_DOOR_ENTRANCE && asset != PROPS_DOOR_LOCKED)
    {
        return false;
    }

    return true;
}

int is_a_fence(int type, int asset)
{
    if (type != ASSET_TYPE_PROPS)
    {
        return false;
    }

    if (asset != PROPS_FENCE && asset != PROPS_FENCE_DIRTY)
    {
        return false;
    }

    return true;
}

int is_npc(int type, int asset)
{
    if (type != ASSET_TYPE_ENEMIES && type != ASSET_TYPE_BOSSES) // all enemies/bosses
    {
        return false;
    }

    return true;
}

int is_a_switch(int type, int asset)
{
    if (type != ASSET_TYPE_PROPS)
    {
        return false;
    }

    if (asset != PROPS_SWITCH)
    {
        return false;
    }

    return true;
}

void attach_to_wall(ENTITY *ent)
{
    VECTOR pos;
    vec_set(&pos, vector((MAP_CELL_SIZE / 2) - OFFSET_FROM_WALL, 0, 0));
    vec_rotate(&pos, &ent->pan);
    vec_add(&pos, &ent->x);

    vec_set(&ent->x, &pos);
    ent->pan += 180;
}

void solid_ent_fnc()
{
    set(my, PASSABLE | LIGHT | NOFILTER | UNLIT | DECAL);
    vec_fill(&my->scale_x, 0.5);
    my->material = mtl_solid;
}

void ceiling_floor_ent_fnc()
{
    set(my, PASSABLE | LIGHT | NOFILTER | UNLIT | DECAL);
    my->material = mtl_solid;
}

void dynamic_object_fnc()
{
    set(my, PASSABLE | LIGHT | NOFILTER | UNLIT);
    vec_fill(&my->scale_x, 0.5);
}

void game_build_walls(Map *map, Cell *cell)
{
    if (!map || !cell)
    {
        return;
    }

    int x = cell->x;
    int y = cell->y;

    int type = cell->type;
    int asset = cell->asset;

    VECTOR pos;
    vec_set(&pos, vector(x, y, 0));

    VECTOR world_pos;
    vec_set(&world_pos, &cell->worldpos);

    int i = 0;
    for (i = 0; i < MAX_DIRECTION_STEP; i++)
    {
        if (game_build_check_direction(map, &pos, &cardinal_dir[i]) == true)
        {
            int n_x = x + cardinal_dir[i].x;
            int n_y = y + cardinal_dir[i].y;

            Cell *neighbour = &map->cell[n_x][n_y];

            VECTOR spawn_dir;
            vec_set(&spawn_dir, vec_diff(NULL, &neighbour->worldpos, &world_pos));
            vec_normalize(&spawn_dir, 1);

            VECTOR spawn_pos;
            vec_set(&spawn_pos, &spawn_dir);
            vec_scale(&spawn_pos, MAP_CELL_SIZE / 2);
            vec_add(&spawn_pos, &world_pos);

            if (is_neighbour_is_door(map, &pos, &cardinal_dir[i]) == true) // make sure to place a doorway texture
            {
                ENTITY *ent = ent_create(wall_doorway_pcx, &spawn_pos, solid_ent_fnc);
                ent->pan = cardinal_rot[i] - 180;
                array_add(ENTITY *, map_solid, ent);
            }
            else
            {
                ENTITY *ent = ent_create(asset_get_filename(type, asset), &spawn_pos, solid_ent_fnc);
                ent->pan = cardinal_rot[i] - 180;
                array_add(ENTITY *, map_solid, ent);
            }
        }
    }
}

void game_build_dynamic_objects(Cell *cell)
{
    if (!cell)
    {
        return;
    }

    int type = cell->type;
    int asset = cell->asset;

    VECTOR spawn_pos;
    vec_set(&spawn_pos, &cell->worldpos);

    ENTITY *ent = ent_create(asset_get_filename(type, asset), &spawn_pos, dynamic_object_fnc);
    ent->material = mtl_solid;

    if (is_cell_allowed_rotation(type, asset) == true && is_npc(type, asset) == false) // but ignore enemies/bosses
    {
        set(ent, DECAL);
        ent->pan = cell->pan;
        ent->material = mtl_two_sided;
        if (is_a_door(type, asset) == true || is_a_fence(type, asset) == true)
        {
            ent->pan = cell->pan - 90; // correct door position
            ent->pan = cycle(ent->pan, 0, 360);
        }
    }

    if (is_a_switch(type, asset) == true)
    {
        attach_to_wall(ent);
    }

    switch (type)
    {
    case ASSET_TYPE_PROPS:
        array_add(ENTITY *, map_props, ent);
        break;

    case ASSET_TYPE_EVENTS:
        array_add(ENTITY *, map_events, ent);
        break;

    case ASSET_TYPE_ITEMS:
        array_add(ENTITY *, map_items, ent);
        break;

    case ASSET_TYPE_ENEMIES:
        array_add(ENTITY *, map_enemies, ent);
        break;

    case ASSET_TYPE_BOSSES:
        array_add(ENTITY *, map_bosses, ent);
        break;
    }
}

void game_build_map(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    Map *current_map = map_get_active(episode);
    if (!current_map)
    {
        return;
    }

    // find center of the map
    VECTOR temp_center;
    vec_set(&temp_center, vector((MAP_WIDTH / 2) * MAP_CELL_SIZE, -(MAP_HEIGHT / 2) * MAP_CELL_SIZE, 0));

    // find scale factor
    var size_width = MAP_WIDTH * MAP_CELL_SIZE;
    var size_height = MAP_HEIGHT * MAP_CELL_SIZE;
    var target_size_width = size_width / ASSET_PREVIEW_IMAGE_WIDTH;
    var target_size_height = size_height / ASSET_PREVIEW_IMAGE_HEIGHT;

    // create ceiling only if there is no weather !
    if (current_map->weather_id <= WEATHER_CLEAR)
    {
        map_ceiling_ent = ent_create(empty_sprite_pcx, vector(temp_center.x, temp_center.y, MAP_CELL_SIZE / 2), ceiling_floor_ent_fnc);
        map_ceiling_ent->tilt = -90;
        vec_set(&map_ceiling_ent->scale_x, vector(target_size_height, target_size_width, 1));
        change_color_from_hsv(&map_ceiling_ent->blue, current_map->ceiling_color[0], current_map->ceiling_color[1], current_map->ceiling_color[2]);
    }

    map_floor_ent = ent_create(empty_sprite_pcx, vector(temp_center.x, temp_center.y, -(MAP_CELL_SIZE / 2)), ceiling_floor_ent_fnc);
    map_floor_ent->tilt = 90;
    vec_set(&map_floor_ent->scale_x, vector(target_size_height, target_size_width, 1));
    change_color_from_hsv(&map_floor_ent->blue, current_map->floor_color[0], current_map->floor_color[1], current_map->floor_color[2]);

    int x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *cell = &current_map->cell[x][y];

            if (cell->type == TYPE_NONE)
            {
                continue;
            }

            if (cell->type == ASSET_TYPE_WALLS)
            {
                game_build_walls(current_map, cell);
            }
            else
            {
                game_build_dynamic_objects(cell);
            }
        }
    }
}

void game_build_weather_settings(Map *map)
{
    if (!map)
    {
        return;
    }

    // apply all the settings at the test level
    // so user can see the changes instantly
    // camera and fog settings
    camera->fog_end = map->fog_end;
    camera->fog_start = map->fog_start;

    camera->clip_near = 0.1;
    camera->clip_far = FOG_MAX_END * 1.25;

    fog_color = 4;
    change_color_from_hsv(&d3d_fogcolor4.blue, map->fog_color[0], map->fog_color[1], map->fog_color[2]);

    if (map->weather_id > WEATHER_CLEAR)
    {
        change_color_from_hsv(&sky_color.blue, map->ceiling_color[0], map->ceiling_color[1], map->ceiling_color[2]);
    }
    else
    {
        vec_set(&sky_color, &d3d_fogcolor4);
    }

    // weather
    weather_update(map->weather_id);
}

void game_build_map_update(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    Map *current_map = map_get_active(episode);
    if (!current_map)
    {
        return;
    }

    // update shaders
    mtl_solid->skill1 = floatv(shader_level_ambient);
    mtl_solid->skill2 = floatv(shader_angle_surface_darken);

    mtl_two_sided->skill1 = floatv(shader_level_ambient);
    mtl_two_sided->skill2 = floatv(shader_angle_surface_darken);

    // apply all the settings at the test level
    // so user can see the changes instantly
    // camera and fog settings
    game_build_weather_settings(current_map);

    if (key_esc)
    {
        editor_switch_state_to(EDITOR_STATE_FROM_TEST_BUILD);
    }
}