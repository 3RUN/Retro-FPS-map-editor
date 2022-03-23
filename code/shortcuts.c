
int is_shortcut_allowed()
{
    if (is_popup_opened == true)
    {
        return false;
    }

    if (editor_state != EDITOR_STATE_EDIT)
    {
        return false;
    }

    return true;
}

void shortcut_remove_binding(var scancode)
{
    if (scancode <= 0)
    {
        return;
    }

    key_set(scancode, NULL);
}

void shortcut_update_binding(var scancode, void *fnc)
{
    if (scancode <= 0)
    {
        return;
    }

    key_set(scancode, NULL);
    key_set(scancode, fnc);
}

void shortcuts_update_from_config(Config *config)
{
    shortcut_remove_binding(scancode_help);
    shortcut_remove_binding(scancode_new);
    shortcut_remove_binding(scancode_open);
    shortcut_remove_binding(scancode_save);
    shortcut_remove_binding(scancode_ep_reset);
    shortcut_remove_binding(scancode_ep_edit);
    shortcut_remove_binding(scancode_reset_map);
    shortcut_remove_binding(scancode_test_run);
    shortcut_remove_binding(scancode_map_settings);
    shortcut_remove_binding(scancode_screenshot);
    shortcut_remove_binding(scancode_settings);
    shortcut_remove_binding(scancode_toggle_debug);
    shortcut_remove_binding(scancode_prior_map);
    shortcut_remove_binding(scancode_next_map);
    shortcut_remove_binding(scancode_shift_map_west);
    shortcut_remove_binding(scancode_shift_map_east);
    shortcut_remove_binding(scancode_shift_map_south);
    shortcut_remove_binding(scancode_shift_map_north);

    scancode_help = engine_key_return_scancode_from_letter(config->short_help);
    scancode_new = engine_key_return_scancode_from_letter(config->short_new);
    scancode_open = engine_key_return_scancode_from_letter(config->short_open);
    scancode_save = engine_key_return_scancode_from_letter(config->short_save);
    scancode_ep_reset = engine_key_return_scancode_from_letter(config->short_ep_reset);
    scancode_ep_edit = engine_key_return_scancode_from_letter(config->short_ep_edit);
    scancode_reset_map = engine_key_return_scancode_from_letter(config->short_reset_map);
    scancode_test_run = engine_key_return_scancode_from_letter(config->short_test_run);
    scancode_map_settings = engine_key_return_scancode_from_letter(config->short_map_settings);
    scancode_screenshot = engine_key_return_scancode_from_letter(config->short_screenshot);
    scancode_settings = engine_key_return_scancode_from_letter(config->short_settings);
    scancode_toggle_debug = engine_key_return_scancode_from_letter(config->short_toggle_debug);
    scancode_prior_map = engine_key_return_scancode_from_letter(config->short_prior_map);
    scancode_next_map = engine_key_return_scancode_from_letter(config->short_next_map);
    scancode_shift_map_west = engine_key_return_scancode_from_letter(config->short_shift_map_west);
    scancode_shift_map_east = engine_key_return_scancode_from_letter(config->short_shift_map_east);
    scancode_shift_map_south = engine_key_return_scancode_from_letter(config->short_shift_map_south);
    scancode_shift_map_north = engine_key_return_scancode_from_letter(config->short_shift_map_north);

    shortcut_update_binding(scancode_help, shortcut_help);
    shortcut_update_binding(scancode_new, shortcut_new);
    shortcut_update_binding(scancode_open, shortcut_open);
    shortcut_update_binding(scancode_save, shortcut_save);
    shortcut_update_binding(scancode_ep_reset, shortcut_ep_reset);
    shortcut_update_binding(scancode_ep_edit, shortcut_ep_edit);
    shortcut_update_binding(scancode_reset_map, shortcut_reset_map);
    shortcut_update_binding(scancode_test_run, shortcut_test_run);
    shortcut_update_binding(scancode_map_settings, shortcut_map_settings);
    shortcut_update_binding(scancode_screenshot, shortcut_screenshot);
    shortcut_update_binding(scancode_settings, shortcut_settings);
    shortcut_update_binding(scancode_toggle_debug, shortcut_toggle_debug);
    shortcut_update_binding(scancode_prior_map, shortcut_prior_map);
    shortcut_update_binding(scancode_next_map, shortcut_next_map);
    shortcut_update_binding(scancode_shift_map_west, shortcut_shift_map_west);
    shortcut_update_binding(scancode_shift_map_east, shortcut_shift_map_east);
    shortcut_update_binding(scancode_shift_map_south, shortcut_shift_map_south);
    shortcut_update_binding(scancode_shift_map_north, shortcut_shift_map_north);
}

void shortcut_help()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    editor_switch_popup_to(EDITOR_POPUP_HELP);
}

void shortcut_new()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    if (is_game_episode_loaded() == true)
    {
        editor_switch_popup_to(EDITOR_POPUP_SURE_NEW);
    }
    else
    {
        editor_switch_popup_to(EDITOR_POPUP_NEW);
    }
}

void shortcut_open()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    if (is_game_episode_loaded() == true)
    {
        editor_switch_popup_to(EDITOR_POPUP_SURE_OPEN);
    }
    else
    {
        editor_switch_popup_to(EDITOR_POPUP_OPEN);
    }
}

void shortcut_save()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    if (key_ctrl)
    {
        strcpy(save_as_filename, ep_save_name);
        editor_switch_popup_to(EDITOR_POPUP_SAVE_AS);
    }
    if (is_game_episode_loaded() == true)
    {
        STRING *temp_ep_name_str = "";
        str_cpy(temp_ep_name_str, ep_save_name);
        str_cat(temp_ep_name_str, " saved.");
        message_add(temp_ep_name_str);

        editor_switch_state_to(EDITOR_STATE_SAVE);
    }
    else
    {
        strcpy(save_as_filename, ep_save_name);
        editor_switch_popup_to(EDITOR_POPUP_SAVE_AS);
    }
}

void shortcut_ep_reset()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    editor_switch_popup_to(EDITOR_POPUP_EP_RESET);
}

void shortcut_ep_edit()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    strcpy(episode_edit_name, def_episode.name);
    strcpy(episode_edit_story_start, def_episode.story_start);
    strcpy(episode_edit_story_end, def_episode.story_end);
    episode_edit_map_count = def_episode.map_count;
    editor_switch_popup_to(EDITOR_POPUP_EP_EDIT);
}

void shortcut_reset_map()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    editor_switch_popup_to(EDITOR_POPUP_MAP_RESET);
}

void shortcut_test_run()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    editor_switch_state_to(EDITOR_STATE_TO_BUILD);
}

void shortcut_map_settings()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    editor_switch_state_to(EDITOR_STATE_TO_MAP_SETTINGS);
}

void shortcut_screenshot()
{
    STRING *screenshot_str = "";
    str_printf(screenshot_str, "shot_%d_%d_%d_", (long)sys_day, (long)sys_month, (long)sys_year);

    STRING *temp_message_str = "";
    str_cpy(temp_message_str, screenshot_str);
    str_cat(temp_message_str, str_for_num(NULL, screenshot_num));
    str_cat(temp_message_str, " was saved.");
    message_add(temp_message_str);

    file_for_screen(screenshot_str, screenshot_num);
    screenshot_num++;
}

void shortcut_settings()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    editor_switch_popup_to(EDITOR_POPUP_SETTINGS);
}

void shortcut_toggle_debug()
{
    is_debug_panel_visible = 1 - is_debug_panel_visible;

    if (is_debug_panel_visible == true)
    {
        message_add("Debug mode is ON");
    }
    else
    {
        message_add("Debug mode is OFF");
    }
}

void shortcut_prior_map()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    active_map_id--;
    active_map_id = clamp(active_map_id, 0, def_episode.map_count - 1);

    Map *active_map = map_get_active(&def_episode);
    if (active_map)
    {
        map_sketch_refresh(active_map);
    }

    message_add(str_printf(NULL, "Moved to prior map! Active map id is %d", (long)active_map_id + 1));
}

void shortcut_next_map()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    active_map_id++;
    active_map_id = clamp(active_map_id, 0, def_episode.map_count - 1);

    Map *active_map = map_get_active(&def_episode);
    if (active_map)
    {
        map_sketch_refresh(active_map);
    }

    message_add(str_printf(NULL, "Moved to next map! Active map id is %d", (long)active_map_id + 1));
}

void shortcut_shift_map_west()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    if (!key_shift)
    {
        return;
    }

    Map *active_map = map_get_active(&def_episode);
    if (!active_map)
    {
        return;
    }

    int x = 0, y = 0;
    for (x = 0; x < MAP_WIDTH; x++)
    {
        Cell saved;
        cell_copy(&saved, &active_map->cell[x][0]);

        for (y = 0; y < MAP_HEIGHT; y++)
        {
            Cell *from = &active_map->cell[x][y + 1];
            Cell *to = &active_map->cell[x][y];
            cell_copy(to, from);
        }

        cell_copy(&active_map->cell[x][MAP_HEIGHT - 1], &saved);
    }
    map_sketch_refresh(active_map);

    message_add("Map shifted to the West");
}

void shortcut_shift_map_east()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    if (!key_shift)
    {
        return;
    }

    Map *active_map = map_get_active(&def_episode);
    if (!active_map)
    {
        return;
    }

    int x = 0, y = 0;
    for (x = 0; x < MAP_WIDTH; x++)
    {
        Cell saved;
        cell_copy(&saved, &active_map->cell[x][MAP_HEIGHT - 1]);

        for (y = MAP_HEIGHT - 1; y >= 0; y--)
        {
            Cell *from = &active_map->cell[x][y - 1];
            Cell *to = &active_map->cell[x][y];
            cell_copy(to, from);
        }

        cell_copy(&active_map->cell[x][0], &saved);
    }
    map_sketch_refresh(active_map);

    message_add("Map shifted to the East");
}

void shortcut_shift_map_south()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    if (!key_shift)
    {
        return;
    }

    Map *active_map = map_get_active(&def_episode);
    if (!active_map)
    {
        return;
    }

    int x = 0, y = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        Cell saved;
        cell_copy(&saved, &active_map->cell[0][y]);

        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *from = &active_map->cell[x + 1][y];
            Cell *to = &active_map->cell[x][y];
            cell_copy(to, from);
        }

        cell_copy(&active_map->cell[MAP_WIDTH - 1][y], &saved);
    }
    map_sketch_refresh(active_map);

    message_add("Map shifted to the South");
}

void shortcut_shift_map_north()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    if (!key_shift)
    {
        return;
    }

    Map *active_map = map_get_active(&def_episode);
    if (!active_map)
    {
        return;
    }

    int x = 0, y = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        Cell saved;
        cell_copy(&saved, &active_map->cell[MAP_WIDTH - 1][y]);

        for (x = MAP_WIDTH - 1; x >= 0; x--)
        {
            Cell *from = &active_map->cell[x - 1][y];
            Cell *to = &active_map->cell[x][y];
            cell_copy(to, from);
        }

        cell_copy(&active_map->cell[0][y], &saved);
    }
    map_sketch_refresh(active_map);

    message_add("Map shifted to the North");
}