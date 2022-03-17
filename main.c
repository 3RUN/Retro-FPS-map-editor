
#include <acknex.h>
#include <windows.h>
#include <strio.c>

#define PRAGMA_POINTER

#define PRAGMA_PATH "code"
#define PRAGMA_PATH "assets"
#define PRAGMA_PATH "assets\\walls"
#define PRAGMA_PATH "assets\\props"
#define PRAGMA_PATH "assets\\events"
#define PRAGMA_PATH "assets\\items"
#define PRAGMA_PATH "assets\\enemies"
#define PRAGMA_PATH "assets\\bosses"

STRING *editor_config_file_str = "editor_config.ini";
STRING *project_name_str = "MapEditor";
STRING *episode_save_folder_str = "episodes\\";
STRING *episode_music_folder_str = "music\\";
STRING *episode_extension_str = ".ep"; // this added to the episode's file name on load/save
STRING *music_extension_str = ".mid";  // only mid music is used

#define MAX_ENTITIES 9999

#define MAP_WIDTH 31
#define MAP_HEIGHT 31
#define MAP_CELL_SIZE 32
#define MAP_Z_POS 0

#define OBJ_ID skill50
#define OBJ_POS_X skill51
#define OBJ_POS_Y skill52
#define OBJ_POS_Z skill53
#define OBJ_TYPE skill54
#define OBJ_ASSET skill55
#define OBJ_TRIGGERED skill56

#define EDITOR_STATE_EDIT 0
#define EDITOR_STATE_OPEN 1
#define EDITOR_STATE_NEW 2
#define EDITOR_STATE_SAVE 3
#define EDITOR_STATE_TO_MAP_SETTINGS 4
#define EDITOR_STATE_MAP_SETTINGS 5
#define EDITOR_STATE_FROM_MAP_SETTINGS 6
#define EDITOR_STATE_TO_BUILD 7
#define EDITOR_STATE_BUILD 8
#define EDITOR_STATE_FROM_BUILD 9
#define EDITOR_STATE_RESET_EPISODE 10
#define EDITOR_STATE_RESET_MAP 11
#define EDITOR_STATE_EXIT 12

// editor booleans
int is_top_bar_used = false;
int is_popup_opened = false;
int is_popup_check_failed = false;
int is_esc_allowed = false;
int is_esc_popup_allowed = false;

// view booleans
int is_grid_visible = true;
int is_walls_visible = true;
int is_objects_visible = true;
int is_cell_links_visible = true;
int is_debug_panel_visible = true;

// mouse position on the grid
int mouse_x = 0;
int mouse_y = 0;

#include "cmd.h"
#include "imgui.h"
#include "ini.h"
#include "dynamic_array.h"
#include "savedir.h"
#include "screenres_list.h"
#include "engine.h"
#include "engine_keybind.h"
#include "debug_panel.h"
#include "config.h"
#include "assets.h"
#include "shaders.h"
#include "game_ep.h"
#include "game_ep_list.h"
#include "game_music_list.h"
#include "game_ep_save_n_load.h"
#include "assets_helper.h"
#include "editor.h"
#include "editor_msg.h"
#include "editor_shortcuts.h"
#include "editor_input.h"
#include "editor_cam_n_grid.h"
#include "editor_popups.h"
#include "editor_asset_params.h"
#include "editor_map_sketch.h"
#include "map_sketcher_tools.h"
#include "editor_main.h"

#include "savedir.c"
#include "screenres_list.c"
#include "engine.c"
#include "engine_keybind.c"
#include "debug_panel.c"
#include "config.c"
#include "assets.c"
#include "shaders.c"
#include "game_ep.c"
#include "game_ep_list.c"
#include "game_music_list.c"
#include "game_ep_save_n_load.c"
#include "assets_helper.c"
#include "editor.c"
#include "editor_msg.c"
#include "editor_shortcuts.c"
#include "editor_input.c"
#include "editor_cam_n_grid.c"
#include "editor_popups.c"
#include "editor_asset_params.c"
#include "editor_map_sketch.c"
#include "map_sketcher_tools.c"
#include "editor_main.c"

void map_editor_startup()
{
	// set launcher window
	// check for existing game folder or create new one
	savedir_create_folder();
	wait_for(savedir_create_folder);

	// set proper path to the config file
	STRING *temp_str = "#256";
	str_cpy(temp_str, editor_config_file_str);
	path_make_absolute(temp_str); // add 'save_dir' full path (in documents folder)

	screen_resolutions_find_all(); // find all available screen resolution (primary monitor only)
	engine_initialize();		   // initialize all engine settings
	assets_initialize();		   // load all editor assets (textures, sprites)
	debug_panel_initialize();	   // initialize debug panel
	shaders_initialize();		   // initialize all shaders used in editor
	imgui_init(0);				   // initialize imgui
	imgui_change_theme();		   // and apply custom theme
	config_initialize(temp_str);   // initialize config (set defaults and load from the config file)engine_initialize()

	messages_initialize();		 // initialize editor message system
	episode_list_initialize();	 // load all episodes from 'episodes' folder
	music_list_initialize();	 // same as above, but for music
	camera_initialize();		 // initialize all camera
	popups_initialize();		 // initialize popups
	map_sketch_initialize();		 // grid of entities to visualize the map while drawing it
	editor_main_initialize();	 // initialize everything related to drawing/editing state ui
	episode_reset(&def_episode); // initialize default episode with default values
}

void on_frame_event()
{
	Map *active_map = map_get_active(&def_episode);

	switch (editor_state)
	{
	case EDITOR_STATE_EDIT:
		grid_get_mouse_pos(&mouse_x, &mouse_y);
		editor_main_update(&def_episode);
		map_sketch_update(&def_episode);
		sketcher_tools_update(active_map, &preview_cell);
		break;

	case EDITOR_STATE_OPEN:
		episode_reset(&def_episode);
		episode_save_name_udpate_to(_str(selected_episode));
		episode_load(ep_save_name, &def_episode);
		map_sketch_refresh(active_map);
		editor_switch_state_to(EDITOR_STATE_EDIT);
		break;

	case EDITOR_STATE_NEW:
		episode_reset(&def_episode);
		episode_change_info(&def_episode, new_episode_name, new_episode_story_start, new_episode_story_end, new_episode_map_count);
		episode_save_name_udpate_to(_str(new_episode_filename));
		episode_save(ep_save_name, &def_episode);
		map_sketch_refresh(active_map);
		editor_switch_state_to(EDITOR_STATE_EDIT);
		break;

	case EDITOR_STATE_SAVE:
		episode_save(ep_save_name, &def_episode);
		editor_switch_state_to(editor_old_state);
		break;

	case EDITOR_STATE_TO_MAP_SETTINGS:
		break;

	case EDITOR_STATE_MAP_SETTINGS:
		break;

	case EDITOR_STATE_FROM_MAP_SETTINGS:
		break;

	case EDITOR_STATE_TO_BUILD:
		break;

	case EDITOR_STATE_BUILD:
		break;

	case EDITOR_STATE_FROM_BUILD:
		break;

	case EDITOR_STATE_RESET_EPISODE:
		episode_reset(&def_episode);
		map_sketch_refresh(active_map);
		editor_switch_state_to(EDITOR_STATE_EDIT);
		break;

	case EDITOR_STATE_RESET_MAP:
		map_reset(active_map);
		map_sketch_refresh(active_map);
		editor_switch_state_to(EDITOR_STATE_EDIT);
		break;

	case EDITOR_STATE_EXIT:
		sys_exit(NULL);
		break;
	}

	debug_panel_update();
	shaders_update();
	camera_n_grid_update(&def_episode);
	messages_update();
	mouse_lock_in_window();

	if (key_f4 && key_alt)
	{
		sys_exit(NULL);
	}
}

void on_exit_event()
{
	assets_destroy_all();
	debug_panel_destroy();
	shaders_destroy();
	messages_destroy();
	episode_list_destroy();
	music_list_destroy();
	popups_destroy();
	map_sketch_destroy();
	editor_main_destroy();
}

void on_esc_event()
{
}

void test()
{
	Map *active_map = map_get_active(&def_episode);

	int x = 0, y = 0, id = 0;
	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			Cell *cell = &active_map->cell[x][y];
			cell->type = integer(random(MAX_ASSET_TYPES));

			switch (cell->type)
			{
			case ASSET_TYPE_WALLS:
				cell->asset = integer(random(TOTAL_WALL_TEXTURES));
				break;

			case ASSET_TYPE_PROPS:
				cell->asset = integer(random(TOTAL_PROPS_TEXTURES));
				break;

			case ASSET_TYPE_EVENTS:
				cell->asset = integer(random(TOTAL_EVENT_TEXTURES));
				break;

			case ASSET_TYPE_ITEMS:
				cell->asset = integer(random(TOTAL_ITEM_TEXTURES));
				break;

			case ASSET_TYPE_ENEMIES:
				cell->asset = integer(random(TOTAL_ENEMY_TEXTURES));
				break;

			case ASSET_TYPE_BOSSES:
				cell->asset = integer(random(TOTAL_BOSS_TEXTURES));
				break;
			}
		}
	}

	map_sketch_refresh(active_map);
}

void main()
{
	on_1 = test;

	max_entities = MAX_ENTITIES;

	on_d3d_lost = imgui_reset;
	on_scanmessage = custom_scan_message;

	on_frame = on_frame_event;
	on_exit = on_exit_event;
	on_esc = on_esc_event;

	level_load("");
}