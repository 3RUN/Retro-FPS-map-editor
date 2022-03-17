#ifndef _EDITOR_DRAW_H_
#define _EDITOR_DRAW_H_

#define PREVIEW_SCALE_FACTOR 2
#define SIDEBAR_ASSET_LIST_CHILD_HEIGHT 215
#define SIDEBAR_PARAM_CHILD_HEIGHT 145

void *asset_draw_list = NULL;

char *editor_draw_popup_id = "##Draw popup id";
char *editor_top_bar_id = "##Top bar menu id";
char *editor_side_bar_id = "##Side bar id";
char *editor_side_bar_category_combo_id = "##Side bar asset category combobox id";
char *editor_preview_parameters_child_id = "##Preview parameters child id";
char *editor_side_bar_asset_list_child_id = "##Side bar asset list child id";

char *selected_asset_category;
char *asset_categories_combobox[MAX_ASSET_TYPES];

char save_as_filename[EPISODE_FILENAME_LENGTH];
char preview_asset_name[ASSET_DESC_LENGTH];

#define DRAW_POPUP_OPEN 0
#define DRAW_POPUP_SURE_OPEN 1
#define DRAW_POPUP_NEW 2
#define DRAW_POPUP_SURE_NEW 3
#define DRAW_POPUP_SAVE_AS 4
#define DRAW_POPUP_SETTINGS 5
#define DRAW_POPUP_EXIT 6
#define DRAW_POPUP_EP_RESET 7
#define DRAW_POPUP_EP_EDIT 8
#define DRAW_POPUP_MAP_RESET 9
#define DRAW_POPUP_HELP 10
#define DRAW_POPUP_WAIT_FOR_INPUT 11

int draw_popup_state = DRAW_POPUP_OPEN;
int draw_popup_old_state = DRAW_POPUP_OPEN;

int selected_type = 0;
int selected_asset = 0;

BMAP *preview_bmap = NULL;

Cell preview_cell;

void editor_draw_initialize();

void editor_draw_reset();

void editor_draw_destroy();

void preview_update(int type, int asset);

void editor_switch_popup_to(int state);

void editor_popups(Episode *episode);

void editor_top_bar(Episode *episode);

void editor_asset_list_item(void *draw_list, int type, int asset);

void editor_side_bar(Episode *episode);

void editor_draw_update(Episode *episode);

#endif