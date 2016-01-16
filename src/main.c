#include "main.h"
#include "checklist_layer.h"


Window *my_window;

void window_load(Window* window) {
  init_item_list();
  
  init_checklist(window);
}


void window_unload(Window* window) {
  
}

void handle_init(void) {
  my_window = window_create();
  
  window_set_window_handlers(my_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload
  });
  
  window_stack_push(my_window, true);
}

void handle_deinit(void) {
  menu_layer_destroy(menu_layer);
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
