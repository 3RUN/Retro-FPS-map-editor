
void music_list_initialize()
{
    music_found_txt = txt_create(MAX_AMOUNT_OF_MUSIC_TO_LOAD, 0);
    music_list_refresh();
}

void music_list_destroy()
{
    if (music_found_txt)
    {
        ptr_remove(music_found_txt);
        music_found_txt = NULL;
    }
}

int scan_music_folder()
{
    STRING *temp_str = "#256";
    str_cpy(temp_str, episode_music_folder_str);
    str_cat(temp_str, "*");
    str_cat(temp_str, music_extension_str);

    return txt_for_dir(music_found_txt, temp_str);
}

void music_selection_reset()
{
    found_music_index = -1;

    if (found_music_total > 0)
    {
        found_music_index = 0;
    }
}

void music_list_refresh()
{
    found_music_index = -1;
    found_music_total = 0;
    found_music_total = scan_music_folder();

    int i = 0;
    for (i = 0; i < found_music_total; i++)
    {
        found_music_listbox[i] = _chr((music_found_txt->pstring)[i]);
    }
}

void play_selection_from_music_list()
{
    STRING *music_to_play_str = "";
    str_cpy(music_to_play_str, episode_music_folder_str);
    str_cat(music_to_play_str, selected_music);
    playing_music_handle = media_play(music_to_play_str, NULL, playing_music_volume);
    playing_music_index = found_music_index;
}