#include <pebble.h>
#include "main_menu.h"

// Windows
Window *my_window;

// Functions
void main_window_load(Window *window);
void main_window_unload(Window *window);
void createMainMenuItems(void);
void main_menu_select_callback(int index, void *ctx);

void handle_init(void) {
  my_window = window_create();
 
 window_set_window_handlers(my_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  window_stack_push(my_window, true);
}

void handle_deinit(void) {
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}

void main_window_load(Window *window) {
 Layer *window_layer = window_get_root_layer(window);
 GRect bounds = layer_get_bounds(window_layer);
 loadMainMenu(bounds, window);
}

void main_window_unload(Window *window) {
  unloadMainMenu();
}