#include <pebble.h>
#include "checklist_layer.h"
#include "item.h"
#include "phone.h"

#define SORT_DELAY 1000

GBitmap *tick_black_bitmap, *tick_white_bitmap;
GFont font;
AppTimer* sortTimer;

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
      .selection_changed = selection_changed,
  });
  
  layer_add_child(window_layer, menu_layer_get_layer(menu_layer));

}

uint16_t get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *context) {
  return itemCount;
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

void reloadMenu() {
  menu_layer_reload_data(menu_layer);
}

void sortTimerCallback(void* data) {
//  app_timer_cancel(sortTimer);
  sortTimer = NULL;

  sortItems();
  reloadMenu();
}

void select_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
  // Check/uncheck
  int row = cell_index->row;
  items[row]->isChecked = !items[row]->isChecked;

  menu_layer_reload_data(menu_layer);
  
  if (sortTimer != NULL) {
    app_timer_reschedule(sortTimer, SORT_DELAY);
  }
  else {
    sortTimer = app_timer_register(SORT_DELAY, sortTimerCallback, NULL);
  }
  
  updateItemStatus(items[row]->id, items[row]->isChecked);
}

void selection_changed(struct MenuLayer *menu_layer, MenuIndex newIndex, MenuIndex oldIndex, void *callback_context) {
  if (sortTimer != NULL) {
    app_timer_reschedule(sortTimer, SORT_DELAY);
  }
}
  

