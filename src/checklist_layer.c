#include <pebble.h>
#include "checklist_layer.h"

GBitmap *tick_black_bitmap, *tick_white_bitmap;
GFont font;

Item* createItem(char* name) {
  Item* item = malloc(sizeof(Item));
  item->name = name;
  item->isChecked = false;
  
  return item;
}

void init_item_list() {
  items[0] = createItem("Milk");
  items[1] = createItem("Bread");
  items[2] = createItem("Peanut Butter");
  items[3] = createItem("Eggs");
  items[4] = createItem("Ground Beef");
  items[5] = createItem("Raisen Bran");
  items[6] = createItem("Chicken Breasts");
  items[7] = createItem("Green Beans");
  items[8] = createItem("Chips");
  items[9] = createItem("Dip");
  
//   items[0] = "Milk";
//   items[1] = "Bread";
//   items[2] = "Peanut Butter";
//   items[3] = "Eggs";
//   items[4] = "Ground Beef";
//   items[5] = "Raisen Bran";
//   items[6] = "Chicken Breasts";
//   items[7] = "Green Beans";
//   items[8] = "Chips";
//   items[9] = "Dip";
}

void init_checklist(Window* window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  font = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  
  tick_black_bitmap = gbitmap_create_with_resource(RESOURCE_ID_TICK_BLACK);
  tick_white_bitmap = gbitmap_create_with_resource(RESOURCE_ID_TICK_WHITE);
  menu_layer = menu_layer_create(bounds);
  menu_layer_set_click_config_onto_window(menu_layer, window);
  menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks) {
      .get_num_rows = get_num_rows_callback,
      .draw_row = draw_row_callback,
      .get_cell_height = get_cell_height_callback,
      .select_click = select_callback,
  });
  
  layer_add_child(window_layer, menu_layer_get_layer(menu_layer));

}

uint16_t get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *context) {
  return CHECKBOX_WINDOW_NUM_ROWS;
}

void draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *context) {
  char* buf = items[(int)cell_index->row]->name;
  GRect bounds = layer_get_bounds(cell_layer);
  
  GSize size = graphics_text_layout_get_content_size(buf, font, bounds, GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft);
  
  int x = bounds.origin.x + (bounds.size.w - size.w) / 2;
  int y = bounds.origin.y - (bounds.size.h - size.h) / 2;
  
  int rightLimit = bounds.size.w - (3*CHECKBOX_WINDOW_BOX_SIZE);
  int rightEdge = x + size.w;
  if (rightEdge > rightLimit) {
    x -= rightEdge - rightLimit;
    if (x < 0) {
      x = 0;
      size.w = rightLimit;
    }
  }
  GRect textBounds = GRect(x, y, size.w, size.h);
  graphics_draw_text(ctx, buf, font, textBounds, GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
  
  // Selected?
  GBitmap *ptr = tick_black_bitmap;
  if(menu_cell_layer_is_highlighted(cell_layer)) {
    graphics_context_set_stroke_color(ctx, GColorWhite);
    ptr = tick_white_bitmap;
  }

  GRect bitmap_bounds = gbitmap_get_bounds(ptr);

  // Draw checkbox
  GRect r = GRect(
    bounds.size.w - (2 * CHECKBOX_WINDOW_BOX_SIZE),
    (bounds.size.h / 2) - (CHECKBOX_WINDOW_BOX_SIZE / 2),
    CHECKBOX_WINDOW_BOX_SIZE, CHECKBOX_WINDOW_BOX_SIZE);
  graphics_draw_rect(ctx, r);
  if(items[cell_index->row]->isChecked) {
    y = bounds.origin.y + bounds.size.h/2;
    graphics_context_set_stroke_width(ctx, 2);
    graphics_draw_line(ctx, GPoint(textBounds.origin.x, y), GPoint(textBounds.origin.x + textBounds.size.w, y));
    graphics_context_set_compositing_mode(ctx, GCompOpSet);
    graphics_draw_bitmap_in_rect(ctx, ptr, GRect(r.origin.x, r.origin.y - 3, bitmap_bounds.size.w, bitmap_bounds.size.h));
  }
}

int16_t get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
  return PBL_IF_ROUND_ELSE(
    menu_layer_is_index_selected(menu_layer, cell_index) ?
      SHORT_CELL_HEIGHT : TALL_CELL_HEIGHT,
    CHECKBOX_WINDOW_CELL_HEIGHT);
}

void moveToChecked(int row) {
  Item* item = items[row];
  for(int i=row+1; i < CHECKBOX_WINDOW_NUM_ROWS; i++) {
    items[i-1] = items[i];
  }  
  
  items[CHECKBOX_WINDOW_NUM_ROWS-1] = item;
}

void moveToUnchecked(int row) {
  int targetIndex = 0;
  for(; targetIndex<row; targetIndex++) {
    if (items[targetIndex]->isChecked) {
      break;
    }
  }
  
  Item* item = items[row];
  for(int i=targetIndex; i<row; i++) {
    items[i+1] = items[i];
  }
  
  items[targetIndex] = item;
  item->isChecked = false;
}

void select_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
  // Check/uncheck
  int row = cell_index->row;
  items[row]->isChecked = !items[row]->isChecked;
  
//   menu_layer_reload_data(menu_layer);
//   psleep(1000);
  
//   if (items[row]->isChecked) {
//     moveToChecked(row);
//   } else {
//     moveToUnchecked(row);
//   }
  
  menu_layer_reload_data(menu_layer);
}
