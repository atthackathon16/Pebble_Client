#include <pebble.h>

static Window *s_main_window;
static TextLayer *s_output_layer;

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  const int text_height = 20;
  const GEdgeInsets text_insets = GEdgeInsets((bounds.size.h - text_height) / 2, 0);

  s_output_layer = text_layer_create(grect_inset(bounds, text_insets));
  text_layer_set_text(s_output_layer, "Press up or down.");
  text_layer_set_text_alignment(s_output_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_output_layer));
}

static void main_window_unload(Window *window) {
  text_layer_destroy(s_output_layer);
}

static void init(void) {
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
}

static void deinit(void) {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}


