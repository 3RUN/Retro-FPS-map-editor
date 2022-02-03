
void editor_load_episodes_initialize()
{
    episodes_list_txt = txt_create(MAX_AMOUNT_OF_EPISODES_TO_LOAD, 0);
}

void editor_load_episodes_destroy()
{
    if (episodes_list_txt)
    {
        ptr_remove(episodes_list_txt);
        episodes_list_txt = NULL;
    }
}

int editor_load_episodes()
{
    static STRING *temp_str = "#256";
    str_cpy(temp_str, "episodes\\*");
    str_cat(temp_str, episode_extension_str);
    path_make_absolute(temp_str);

    return txt_for_dir(episodes_list_txt, temp_str);
}

void editor_load_refresh_list()
{
    found_episode_index = -1;
    found_episodes_total = 0;
    found_episodes_total = editor_load_episodes();

    int i = 0;
    for (i = 0; i < found_episodes_total; i++)
    {
        found_episodes_listbox[i] = _chr((episodes_list_txt->pstring)[i]);
    }
}

void editor_load_update(Episode *e)
{
    if (!e)
    {
        return;
    }

    imgui_start_imode();
    imgui_set_next_window_pos((screen_size.x / 2) - (LOAD_BROWSER_WINDOW_WIDTH / 2), (screen_size.y / 2) - (LOAD_BROWSER_WINDOW_HEIGHT / 2), ImGuiCond_Always);
    imgui_set_next_window_size(LOAD_BROWSER_WINDOW_WIDTH, -1, ImGuiCond_Always);
    int load_episode_window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin("Load Episode", NULL, load_episode_window_flags);

    int editor_load_episode_child_window_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    var editor_load_browser_width = imgui_get_content_region_avail_width();
    imgui_begin_child("##Editor Load Browser Child", vector(editor_load_browser_width, LOAD_BROWSER_WINDOW_HEIGHT - 60, 0), 1, editor_load_episode_child_window_flags);

    if (found_episodes_total <= 0)
    {
        imgui_text("'Documents\\MapEditor\\episodes' - folder is empty.");
    }
    else
    {
        imgui_push_item_width(-1);
        if (imgui_list_box("##Editor Load Browser Listbox", &found_episode_index, found_episodes_listbox, found_episodes_total, found_episodes_total))
        {
            int i = 0;
            for (i = 0; i < found_episodes_total; i++)
            {
                if (found_episode_index == i)
                {
                    selected_episode = found_episodes_listbox[i];
                }
            }
        }
        imgui_pop_item_width();
    }

    imgui_end_child();

    var button_width = ((LOAD_BROWSER_WINDOW_WIDTH - (engine_theme_win_padding[0] * 2)) / 3) - 3;
    if (imgui_button_withsize("Refresh", button_width, LOAD_BROWSER_WINDOW_BUTTON_HEIGHT))
    {
        episode_loading_failed = false;
        editor_load_refresh_list();
    }
    imgui_same_line();
    if (imgui_button_withsize("Load", button_width, LOAD_BROWSER_WINDOW_BUTTON_HEIGHT))
    {
        if (found_episode_index >= 0)
        {
            episode_reset(e);

            episode_load(selected_episode, e);

            editor_create_grid_ents();
            map_editor_start(e);
            editor_browser_music_refresh_list();

            Map *m = map_get_active(e);
            editor_update_grid_ents(m);
            map_editor_weather_refresh(e);

            editor_switch_state_to(STATE_EDITOR);

            static STRING *trim_the_name_str = "";
            str_cpy(trim_the_name_str, _str(selected_episode));
            var num = str_len(episode_extension_str);
            str_trunc(trim_the_name_str, num);

            strcpy(episode_save_name, _chr(trim_the_name_str));
            episode_loading_failed = false;
        }
        else
        {
            episode_loading_failed = true;
        }
    }
    imgui_same_line();
    if (imgui_button_withsize("Back", button_width, LOAD_BROWSER_WINDOW_BUTTON_HEIGHT))
    {
        episode_loading_failed = false;
        editor_switch_state_to(STATE_MAIN_MENU);
    }

    if (episode_loading_failed == true)
    {
        imgui_push_style_color(ImGuiCol_TextDisabled, color4_red);
        imgui_text_disabled("      Select an episode from the list to load it!");
        imgui_pop_style_color(1);
    }

    imgui_end();
    imgui_end_imode();
}