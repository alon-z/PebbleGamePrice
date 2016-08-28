#include <pebble.h>

// Settings
#define GAMES_SIZE 3
const char *games[] = {"Grand Theft Auto V", "Fallout 4", "Rocket League"};

// Windows
Window *my_window;

// Main Menu
SimpleMenuLayer *main_menu;
static SimpleMenuSection main_menu_sections[1];
SimpleMenuItem main_menu_items[GAMES_SIZE];

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
 
 // Menu
 createMainMenuItems();
 main_menu_sections[0] = (SimpleMenuSection) {
    .num_items = GAMES_SIZE,
    .items = main_menu_items,
  };
 main_menu = simple_menu_layer_create(bounds, window, main_menu_sections, GAMES_SIZE, NULL);
 layer_add_child(window_layer, simple_menu_layer_get_layer(main_menu));
}

void main_window_unload(Window *window) {
  simple_menu_layer_destroy(main_menu);
}

void createMainMenuItems(void) {
 unsigned long i;
 for(i = 0; i < GAMES_SIZE; i++)
  {
    main_menu_items[i] = (SimpleMenuItem) {
      .title = games[i],
      .subtitle = "0.00$",
      .callback = main_menu_select_callback
    };
  }
}

void main_menu_select_callback(int index, void *ctx) {
  main_menu_items[index].subtitle = "You've hit select here!";
  layer_mark_dirty(simple_menu_layer_get_layer(main_menu));
}