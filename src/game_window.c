#include <pebble.h>
#include "game_window.h"

// Windows
Window *game_window;

// Functions
void game_window_load(Window *window);
void game_window_unload(Window *window);

// Components
static TextLayer *s_text_layer;

void game_window_load(Window *window) {
 Layer *window_layer = window_get_root_layer(window);
 GRect bounds = layer_get_bounds(window_layer);
	
	// Create a TextLayer
	s_text_layer = text_layer_create(bounds);
	
	// Set some properties
	text_layer_set_text_color(s_text_layer, GColorWhite);
	text_layer_set_background_color(s_text_layer, GColorBlack);
	text_layer_set_overflow_mode(s_text_layer, GTextOverflowModeWordWrap);
	
	
	// Set the text shown
	text_layer_set_text(s_text_layer, "Hello, World!");

	// Add to the Window
	layer_add_child(window_layer, text_layer_get_layer(s_text_layer));
}

void game_window_unload(Window *window) {
	
	// Destroy the TextLayer
	text_layer_destroy(s_text_layer);
   window_destroy(window);
}

void load_game_window(const char game_name[]) {
  game_window = window_create();
 
 window_set_window_handlers(game_window, (WindowHandlers) {
    .load = game_window_load,
    .unload = game_window_unload
  });

  window_stack_push(game_window, true);
}