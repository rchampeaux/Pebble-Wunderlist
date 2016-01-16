#pragma once

#include "pebble.h"

#define CHECKBOX_WINDOW_NUM_ROWS    10
#define CHECKBOX_WINDOW_BOX_SIZE    12
#define CHECKBOX_WINDOW_CELL_HEIGHT 44
#define SHORT_CELL_HEIGHT 30
#define TALL_CELL_HEIGHT 30

typedef struct _Item {
  char* name;
  bool isChecked;
} Item;

MenuLayer *menu_layer;
static Item* items[CHECKBOX_WINDOW_NUM_ROWS];

void init_item_list();

void init_checklist(Window* window);

uint16_t get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *context);
void draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *context);
int16_t get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context);
void moveToChecked(int row);
void moveToUnchecked(int row);
void select_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context);

