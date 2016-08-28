#include <pebble.h>
#include "game_window.h"

// Windows
Window *game_window;

// Functions
void game_window_load(Window *window);
void game_window_unload(Window *window);
static void inbox_received_callback(DictionaryIterator *iterator, void *context);
static void inbox_dropped_callback(AppMessageResult reason, void *context);
static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context);
static void outbox_sent_callback(DictionaryIterator *iterator, void *context);

// Components
static TextLayer *s_text_layer;

void game_window_load(Window *window) {
 Layer *window_layer = window_get_root_layer(window);
 GRect bounds = layer_get_bounds(window_layer);
  
  // Create a TextLayer
  s_text_layer = text_layer_create(GRect(5, bounds.size.h/10, bounds.size.w-10, bounds.size.h/10));
  
	// Set some properties
  text_layer_set_text_color(s_text_layer, GColorWhite);
  text_layer_set_background_color(s_text_layer, GColorBlack);

  // Set the text shown
	text_layer_set_text(s_text_layer, "Hello, World!");

	// Register callbacks
	app_message_register_inbox_received(inbox_received_callback);
	app_message_register_inbox_dropped(inbox_dropped_callback);
	app_message_register_outbox_failed(outbox_failed_callback);
	app_message_register_outbox_sent(outbox_sent_callback);
	
	// Open AppMessage
	const int inbox_size = 128;
	const int outbox_size = 128;
	app_message_open(inbox_size, outbox_size);

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

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {

}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}