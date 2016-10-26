#include <pebble.h>

static Window *s_window;
static TextLayer *s_text_layer;

static void prv_restart(void* data) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "restarting...");

  // will close the app
  window_stack_pop_all(false);

  // schedule a wakeup 2s after now to make sure the watchface gets restarted
  // NOTE: we do 2s instead of 1s to avoid a potential rare race condition where the
  // current second flips after we obtained the current time
  const time_t future_time = time(NULL) + 2;
  APP_LOG(APP_LOG_LEVEL_DEBUG, "will restart at %lu", future_time);
  wakeup_schedule(future_time, 0, false);

}

static void prv_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_text_layer = text_layer_create(GRect(0, 72, bounds.size.w, 20));
  text_layer_set_text(s_text_layer, "I am a watchface");
  text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_text_layer));

  app_timer_register(5000, prv_restart, NULL);
}

static void prv_window_unload(Window *window) {
  text_layer_destroy(s_text_layer);
}

static void prv_init(void) {
  s_window = window_create();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = prv_window_load,
    .unload = prv_window_unload,
  });
  window_stack_push(s_window, false);
}

static void prv_deinit(void) {
  window_destroy(s_window);
}

int main(void) {
  prv_init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", s_window);

  app_event_loop();
  prv_deinit();
}
