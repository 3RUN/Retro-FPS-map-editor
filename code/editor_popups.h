#ifndef _EDITOR_POPUPS_H_
#define _EDITOR_POPUPS_H_

#define EDITOR_POPUP_OPEN_WIDTH 395
#define EDITOR_POPUP_OPEN_HEIGHT 320
#define EDITOR_POPUP_OPEN_SURE_WIDTH 340

#define EDITOR_POPUP_ABOUT_CHILD_WIDTH 270
#define EDITOR_POPUP_ABOUT_CHILD_HEIGHT 450

#define EDITOR_POPUP_NEW_WIDTH 395
#define EDITOR_POPUP_NEW_SURE_WIDTH 320

#define EDITOR_POPUP_SAVE_AS_WIDTH 320

#define EDITOR_POPUP_SETTINGS_WIDTH 480
#define EDITOR_POPUP_EXIT_WIDTH 208

#define EDITOR_POPUP_EPISODE_EDIT_WIDTH 395
#define EDITOR_POPUP_RESET_MAP_WIDTH 300

#define EDITOR_POPUP_BUTTON_HEIGHT 24
#define EDITOR_POPUP_COMBOBOX_WIDTH 300

#define MUSIC_POPUP_MUSIC_BROWSER_WIDTH 395
#define MUSIC_POPUP_MUSIC_BROWSER_HEIGHT 320

char *editor_popup_save_as_input_id = "##Editor save as input field";

char *editor_popup_episode_browser_id = "##Editor episode browser child";
char *editor_popup_episode_listbox_id = "##Editor episode browser listbox";

char *editor_popup_new_filename_input_id = "##New filename";
char *editor_popup_new_episode_name_id = "##New episode name";
char *editor_popup_new_episode_start_story_id = "##New episode start story";
char *editor_popup_new_episode_end_story_id = "##New episode end story";
char *editor_popup_new_episode_map_slider_id = "##New episode map slider";

char *editor_popup_episode_edit_name_id = "##Episode edit name";
char *editor_popup_episode_edit_start_story_id = "##Episode edit start story";
char *editor_popup_episode_edit_end_story_id = "##Episode edit end story";
char *editor_popup_episode_edit_map_slider_id = "##Episode edit map slider";

char *editor_popup_settings_display_combo_id = "##Display mode combo";
char *editor_popup_settings_resolution_combo_id = "##Resolution combo";
char *editor_popup_settings_bg_color_picker_id = "##Background color picker";
char *editor_popup_settings_grid_color_picker_id = "##Grid color picker";

char *editor_popup_music_browser_child_id = "##Music browser child";
char *editor_popup_music_browser_listbox_id = "##Music browser listbox";
char *editor_popup_music_browser_volume_slider_id = "##Music browser volume slider";

char *editor_popup_about_child_id = "##About child";

char new_filename[EPISODE_FILENAME_LENGTH];
char new_name[EPISODE_NAME_LENGTH];
char new_start_story[EPISODE_START_STORY_LENGTH];
char new_end_story[EPISODE_END_STORY_LENGTH];

char save_as_filename[EPISODE_FILENAME_LENGTH];

char episode_edit_name[EPISODE_NAME_LENGTH];
char episode_edit_start_story[EPISODE_START_STORY_LENGTH];
char episode_edit_end_story[EPISODE_END_STORY_LENGTH];

int new_map_count = 1;
int episode_edit_map_count = 1;
int is_episode_creation_failed = false;
int is_episode_save_as_failed = false;
int is_episode_edit_failed = false;

STRING *editor_popup_open_str = "Please select episode to open.";
STRING *editor_popup_open_empty_folder_str = "'Documents\\MapEditor\\episodes' - folder is empty.";

STRING *editor_popup_open_sure_str = "Are you sure you want to open different episode?\nAll unsaved data will be lost!";

STRING *editor_popup_new_filename_str = "File name";
STRING *editor_popup_new_filename_tooltip_str = "The file name to save episode as. Character limit %d.";
STRING *editor_popup_new_episode_name_str = "Episode name";
STRING *editor_popup_new_episode_name_tooltip_str = "The name of the episode. Character limit %d.";
STRING *editor_popup_new_episode_start_story_str = "Story beginning";
STRING *editor_popup_new_episode_end_story_str = "Story ending";
STRING *editor_popup_new_episode_start_story_tooltip_str = "Short episode story showed at the start. Character limit %d.";
STRING *editor_popup_new_episode_end_story_tooltip_str = "Short episode story showed when game is finished. Character limit %d.";
STRING *editor_popup_new_episode_map_count_str = "Map count";
STRING *editor_popup_new_episode_map_count_tooltip_str = "Amount of maps in the episode. Max %d.";
STRING *editor_popup_new_creation_failed_str = "Make sure to enter filename, name and start/end stories!";
STRING *editor_popup_new_file_exist_str = "          Episode with this name already exists!";
STRING *editor_popup_new_create_str = "";

STRING *editor_popup_new_sure_str = "Are you sure you want to create a new episode?\nAll unsaved data will be lost!";

STRING *editor_popup_save_as_str = "Save current episode";
STRING *editor_popup_save_as_button_str = "";
STRING *editor_popup_save_as_failed_str = "          You forgot to enter file name!";
STRING *editor_popup_save_as_overwrite_str = "      Episode with this name already exists!";

STRING *editor_popup_settings_hover_cell_tooltip_str = "Hovering cell tooltip: ";
STRING *editor_popup_settings_background_color_str = "Background color: ";
STRING *editor_popup_settings_grid_color_str = "Grid color:       ";

STRING *editor_popup_controlls_str = "Controlls:";
STRING *editor_popup_controlls_cmd_0_str = "PICK TOOL:      MBL + ALT (hold)";
STRING *editor_popup_controlls_cmd_1_str = "DRAW ONCE:      MBL";
STRING *editor_popup_controlls_cmd_2_str = "DRAW ENDLESS:   MBL + SHIFT (hold)";
STRING *editor_popup_controlls_cmd_3_str = "ERASE ONCE:     MBR";
STRING *editor_popup_controlls_cmd_4_str = "ERASE ENDLESS:  MBR + SHIFT (hold)";
STRING *editor_popup_controlls_cmd_5_str = "ROTATE CELL:    R";
STRING *editor_popup_shortcuts_str = "Shortcuts";
STRING *editor_popup_shortcut_cmd_0_str = "HELP: F1";
STRING *editor_popup_shortcut_cmd_1_str = "SETTINGS: F2";
STRING *editor_popup_shortcut_cmd_2_str = "SCREENSHOT: F6";
STRING *editor_popup_shortcut_cmd_3_str = "EXIT: ALT + F4";
STRING *editor_popup_shortcut_cmd_4_str = "SAVE (SAVE AS): CTRL + S (+ ALT)";
STRING *editor_popup_shortcut_cmd_5_str = "OPEN EPISODE: CTRL + O";
STRING *editor_popup_shortcut_cmd_6_str = "NEW EPISODE: CTRL + N";
STRING *editor_popup_shortcut_cmd_7_str = "EDIT EPISODE: CTRL + E";
STRING *editor_popup_shortcut_cmd_8_str = "RESET MAP: CTRL + R";
STRING *editor_popup_shortcut_cmd_9_str = "MAP SETTINGS: CTRL + M";
STRING *editor_popup_shortcut_cmd_10_str = "MAP TEST BUILD: CTRL + T";
STRING *editor_popup_shortcut_cmd_11_str = "MAP SHIFT UP: CTRL + CUU";
STRING *editor_popup_shortcut_cmd_12_str = "MAP SHIFT DOWN: CTRL + CUD";
STRING *editor_popup_shortcut_cmd_13_str = "MAP SHIFT RIGHT: CTRL + CUR";
STRING *editor_popup_shortcut_cmd_14_str = "MAP SHIFT LEFT: CTRL + CUL";
STRING *editor_popup_shortcut_cmd_15_str = "MAP PRIOR: CTRL + PAGEDN";
STRING *editor_popup_shortcut_cmd_16_str = "MAP NEXT: CTRL + PAGEUP";

STRING *editor_popup_episode_saved_at_str = "Episodes saved at:";
STRING *editor_popup_episode_save_path_str = "username\\Documents\\MapEditor\\episodes";
STRING *editor_popup_credit_name_str = "Created by:";
STRING *editor_popup_credit_info_0_str = "Magomet Kochkarov aka 3RUN";
STRING *editor_popup_credit_email_str = "Email:";
STRING *editor_popup_credit_info_1_str = "parkour09@mail.ru";

STRING *editor_popup_exit_str = "Are you sure you want to exit?\nAll unsaved data will be lost!";

STRING *editor_popup_episode_edit_str = "Edit episode";
STRING *editor_popup_episode_edit_failed_str = "  Make sure to enter episode name and start/end stories!";

STRING *editor_popup_reset_map_str = "Are you sure you want to reset current map?";

STRING *editor_popup_currently_used_music_str = "";
STRING *editor_popup_currently_playing_music_str = "";
STRING *editor_popup_music_browser_str = "Music browser";
STRING *editor_popup_music_browser_empty_folder_str = "'Music' - folder is empty.";
STRING *editor_popup_music_browser_used_none_str = "Currently used: none";
STRING *editor_popup_music_browser_used_str = "Currently used: ";
STRING *editor_popup_music_browser_playing_str = "Currently playing: ";
STRING *editor_popup_music_browser_playing_none_str = "Currently playing: none";
STRING *editor_popup_music_browser_playing_failed_str = "         Please, select music file to play/use.";

// resolution config
STRING *graphics_resolution_available_list_str[SCREEN_RESOLUTION_MAX];
STRING *graphics_resolution_currently_used_str = "None";
STRING *graphics_res_str = "Resolution:";

// display mode config
STRING *graphics_display_mode_list_str[DISPLAY_MODES_MAX]; // list of available display modes (windowed, windowed fullscreen, fullscreen)
STRING *graphics_display_currently_used_str = "None";      // currently set display mode
STRING *graphics_display_mode_str = "Display mode:";
STRING *graphics_display_windowed_str = "Windowed";
STRING *graphics_display_windowed_fullscreen_str = "Borderless";

void editor_popups_initialize(Episode *episode);

void editor_popups_refresh(Episode *episode);

void editor_popups_destroy();

void editor_popup_open(Episode *episode);

void editor_popup_open_sure();

void editor_popup_new(Episode *episode);

void editor_popup_new_sure();

void editor_popup_save_as(Episode *episode);

void editor_popup_settings(Episode *episode);

void editor_popup_about();

void editor_popup_episode_edit(Episode *episode);

void editor_popup_reset_map(Episode *episode);

void editor_popup_music_browser(Episode *episode);

void editor_popup_exit();

#endif