
void asset_create_texture(array_t *array, BMAP *source, STRING *description, int type, int u, int v)
{
    if (!array)
    {
        return;
    }

    Asset *asset = sys_malloc(sizeof(Asset));
    if (!asset)
    {
        return;
    }

    asset->bmap = bmap_createblack(32, 32, 24);
    bmap_blitpart(asset->bmap, source, nullvector, nullvector, vector(u, v, 0), vector(MAP_CELL_SIZE, MAP_CELL_SIZE, 0));
    strcpy(asset->description, description);
    asset->type = type;
    asset->index = array_get_count(array);

    array_add(Asset *, array, asset);
}

void asset_create_object(array_t *array, BMAP *source, STRING *description, int type, int index, int u, int v)
{
}

void assets_initialize()
{
    wall_textures = array_create(Asset *, 1);
    floor_textures = array_create(Asset *, 1);
    ceiling_textures = array_create(Asset *, 1);

    // walls
    {
        asset_create_texture(wall_textures, wall_textures_tga, "Grey brick 1", ASSET_TYPE_WALL, 29, 29);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey brick 2", ASSET_TYPE_WALL, 94, 29);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey brick 3", ASSET_TYPE_WALL, 159, 29);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey brick / flag", ASSET_TYPE_WALL, 224, 29);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey brick / Hitler", ASSET_TYPE_WALL, 289, 29);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey brick / eagle", ASSET_TYPE_WALL, 354, 29);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey brick / sign", ASSET_TYPE_WALL, 419, 29);

        asset_create_texture(wall_textures, wall_textures_tga, "Dirty brick 1", ASSET_TYPE_WALL, 29, 94);
        asset_create_texture(wall_textures, wall_textures_tga, "Dirty brick 2", ASSET_TYPE_WALL, 94, 94);
        asset_create_texture(wall_textures, wall_textures_tga, "Cell", ASSET_TYPE_WALL, 159, 94);
        asset_create_texture(wall_textures, wall_textures_tga, "Cell / skeleton", ASSET_TYPE_WALL, 224, 94);
        asset_create_texture(wall_textures, wall_textures_tga, "Blue brick 1", ASSET_TYPE_WALL, 289, 94);
        asset_create_texture(wall_textures, wall_textures_tga, "Blue brick 2", ASSET_TYPE_WALL, 354, 94);
        asset_create_texture(wall_textures, wall_textures_tga, "Blue brick / sign", ASSET_TYPE_WALL, 419, 94);

        asset_create_texture(wall_textures, wall_textures_tga, "Wood", ASSET_TYPE_WALL, 29, 159);
        asset_create_texture(wall_textures, wall_textures_tga, "Wood / eagle", ASSET_TYPE_WALL, 94, 159);
        asset_create_texture(wall_textures, wall_textures_tga, "Wood / Hitler", ASSET_TYPE_WALL, 159, 159);
        asset_create_texture(wall_textures, wall_textures_tga, "Wood / iron cross", ASSET_TYPE_WALL, 224, 159);
        asset_create_texture(wall_textures, wall_textures_tga, "Steal", ASSET_TYPE_WALL, 289, 159);
        asset_create_texture(wall_textures, wall_textures_tga, "Steal / sign", ASSET_TYPE_WALL, 354, 159);
        asset_create_texture(wall_textures, wall_textures_tga, "Red brick", ASSET_TYPE_WALL, 419, 159);

        asset_create_texture(wall_textures, wall_textures_tga, "Red brick / swastika", ASSET_TYPE_WALL, 29, 224);
        asset_create_texture(wall_textures, wall_textures_tga, "Red brick / flag", ASSET_TYPE_WALL, 94, 224);
        asset_create_texture(wall_textures, wall_textures_tga, "Multicolor brick", ASSET_TYPE_WALL, 159, 224);
        asset_create_texture(wall_textures, wall_textures_tga, "Stone wall 1", ASSET_TYPE_WALL, 224, 224);
        asset_create_texture(wall_textures, wall_textures_tga, "Stone wall 2", ASSET_TYPE_WALL, 289, 224);
        asset_create_texture(wall_textures, wall_textures_tga, "Stone wall / flag", ASSET_TYPE_WALL, 354, 224);
        asset_create_texture(wall_textures, wall_textures_tga, "Stone wall / swastika", ASSET_TYPE_WALL, 419, 224);

        asset_create_texture(wall_textures, wall_textures_tga, "Grey wall 1", ASSET_TYPE_WALL, 29, 289);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey wall 2", ASSET_TYPE_WALL, 94, 289);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey wall / Hitler", ASSET_TYPE_WALL, 159, 289);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey wall / map", ASSET_TYPE_WALL, 224, 289);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey wall / vent", ASSET_TYPE_WALL, 289, 289);
        asset_create_texture(wall_textures, wall_textures_tga, "Blue wall", ASSET_TYPE_WALL, 354, 289);
        asset_create_texture(wall_textures, wall_textures_tga, "Blue wall / swastika", ASSET_TYPE_WALL, 419, 289);

        asset_create_texture(wall_textures, wall_textures_tga, "Blue wall / skull", ASSET_TYPE_WALL, 29, 354);
        asset_create_texture(wall_textures, wall_textures_tga, "Brown stone 1", ASSET_TYPE_WALL, 94, 354);
        asset_create_texture(wall_textures, wall_textures_tga, "Brown stone 2", ASSET_TYPE_WALL, 159, 354);
        asset_create_texture(wall_textures, wall_textures_tga, "Brown marble 1", ASSET_TYPE_WALL, 224, 354);
        asset_create_texture(wall_textures, wall_textures_tga, "Brown marble 2", ASSET_TYPE_WALL, 289, 354);
        asset_create_texture(wall_textures, wall_textures_tga, "Brown marble / flag", ASSET_TYPE_WALL, 354, 354);
        asset_create_texture(wall_textures, wall_textures_tga, "Door excavation (side of door)", ASSET_TYPE_WALL, 419, 354);

        asset_create_texture(wall_textures, wall_textures_tga, "Elevator wall", ASSET_TYPE_WALL, 29, 419);
        asset_create_texture(wall_textures, wall_textures_tga, "Elevator (on)", ASSET_TYPE_WALL, 94, 419);
        asset_create_texture(wall_textures, wall_textures_tga, "Elevator (off)", ASSET_TYPE_WALL, 159, 419);
        asset_create_texture(wall_textures, wall_textures_tga, "Elevator door", ASSET_TYPE_WALL, 224, 419);
        asset_create_texture(wall_textures, wall_textures_tga, "Entrance to level", ASSET_TYPE_WALL, 289, 419);
        asset_create_texture(wall_textures, wall_textures_tga, "Locked door", ASSET_TYPE_WALL, 354, 419);
        asset_create_texture(wall_textures, wall_textures_tga, "Door", ASSET_TYPE_WALL, 419, 419);
    }

    // floor
    {
        asset_create_texture(floor_textures, floor_textures_tga, "Marble", ASSET_TYPE_FLOOR, 31, 31);
        asset_create_texture(floor_textures, floor_textures_tga, "Tiled", ASSET_TYPE_FLOOR, 96, 31);
        asset_create_texture(floor_textures, floor_textures_tga, "Parquet", ASSET_TYPE_FLOOR, 161, 31);

        asset_create_texture(floor_textures, floor_textures_tga, "Stone", ASSET_TYPE_FLOOR, 31, 96);
        asset_create_texture(floor_textures, floor_textures_tga, "Grass", ASSET_TYPE_FLOOR, 96, 96);
        asset_create_texture(floor_textures, floor_textures_tga, "Dirt", ASSET_TYPE_FLOOR, 161, 96);

        asset_create_texture(floor_textures, floor_textures_tga, "Bricks", ASSET_TYPE_FLOOR, 31, 161);
        asset_create_texture(floor_textures, floor_textures_tga, "Dry dirt", ASSET_TYPE_FLOOR, 96, 161);
        asset_create_texture(floor_textures, floor_textures_tga, "Concrete", ASSET_TYPE_FLOOR, 161, 161);
    }

    // ceiling
    {
        asset_create_texture(floor_textures, floor_textures_tga, "Ceiling 1", ASSET_TYPE_FLOOR, 31, 31);
        asset_create_texture(floor_textures, floor_textures_tga, "Ceiling 2", ASSET_TYPE_FLOOR, 96, 31);
        asset_create_texture(floor_textures, floor_textures_tga, "Ceiling 3", ASSET_TYPE_FLOOR, 161, 31);

        asset_create_texture(floor_textures, floor_textures_tga, "Ceiling 4", ASSET_TYPE_FLOOR, 31, 96);
        asset_create_texture(floor_textures, floor_textures_tga, "Ceiling 5", ASSET_TYPE_FLOOR, 96, 96);
        asset_create_texture(floor_textures, floor_textures_tga, "Ceiling 6", ASSET_TYPE_FLOOR, 161, 96);

        asset_create_texture(floor_textures, floor_textures_tga, "Ceiling 7", ASSET_TYPE_FLOOR, 31, 161);
        asset_create_texture(floor_textures, floor_textures_tga, "Ceiling 8", ASSET_TYPE_FLOOR, 96, 161);
        asset_create_texture(floor_textures, floor_textures_tga, "Ceiling 9", ASSET_TYPE_FLOOR, 161, 161);
    }
}

void assets_destroy_array(array_t *array)
{
    if (!array)
    {
        return;
    }

    Asset *temp_asset;
    array_enumerate_begin(Asset *, array, temp_asset)
    {
        if (temp_asset->bmap)
        {
            ptr_remove(temp_asset->bmap);
            temp_asset->bmap = NULL;
        }
        sys_free(temp_asset);
    }
    array_enumerate_end(array);
    array_destroy(array);
}

void assets_destroy()
{
    assets_destroy_array(wall_textures);
    assets_destroy_array(floor_textures);
    assets_destroy_array(ceiling_textures);
}