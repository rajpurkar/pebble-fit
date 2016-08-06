#include "main_window.h"

static Window *s_window;
static TextLayer *title_layer;
static TextLayer *subtitle_layer;

static TextLayer* make_text_layer(GRect bounds, GFont font) {
  TextLayer *this = text_layer_create(bounds);
  text_layer_set_background_color(this, GColorClear);
  text_layer_set_text_color(this, GColorWhite);
  text_layer_set_text_alignment(this, GTextAlignmentCenter);
  text_layer_set_font(this, font);
  return this;
}

static void window_load(Window * window) {
  // Get the bounds of the root layer
  Layer *root_layer  = window_get_root_layer(window);
  window_set_background_color(window, GColorBlack);

  GRect bounds = layer_get_bounds(root_layer);
  float center = bounds.size.h /= 2;

  // Create a text layer, and set the text
  int height = 30;
  title_layer = make_text_layer(GRect(0, center - height, bounds.size.w, height), fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
  text_layer_set_text(title_layer, "Pebble Fit");

  subtitle_layer = make_text_layer(GRect(0, center, bounds.size.w, center + height), fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text(subtitle_layer, "A Better Today");


  // Add text layer to the window
  layer_add_child(root_layer, text_layer_get_layer(title_layer));
    layer_add_child(root_layer, text_layer_get_layer(subtitle_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(title_layer);
  text_layer_destroy(subtitle_layer);
  window_destroy(s_window);
}

void main_window_update_steps(int s_step_count, int s_step_goal) {
    static char s_current_steps_buffer[16];
    int thousands = s_step_count / 1000;
    int hundreds = s_step_count % 1000;
    static char s_emoji[5];

    if(s_step_count >= s_step_goal) {
      text_layer_set_text_color(subtitle_layer, GColorJaegerGreen);
      snprintf(s_emoji, sizeof(s_emoji), "\U0001F60C");
    } else {
      text_layer_set_text_color(subtitle_layer, GColorPictonBlue);
      snprintf(s_emoji, sizeof(s_emoji), "\U0001F4A9");
    }

    if(thousands > 0) {
      snprintf(s_current_steps_buffer, sizeof(s_current_steps_buffer),
        "%d,%03d %s", thousands, hundreds, s_emoji);
    } else {
      snprintf(s_current_steps_buffer, sizeof(s_current_steps_buffer),
        "%d %s", hundreds, s_emoji);
    }

    text_layer_set_text(subtitle_layer, s_current_steps_buffer);
}

void main_window_update_time(struct tm *tick_time) {
  static char s_current_time_buffer[8];
  strftime(s_current_time_buffer, sizeof(s_current_time_buffer),
           clock_is_24h_style() ? "%H:%M" : "%l:%M", tick_time);
  text_layer_set_text(title_layer, s_current_time_buffer);
}

void main_window_push() {
  s_window = window_create();

  window_set_window_handlers(s_window, (WindowHandlers) {
    .load  = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_window, true);
}

void main_window_remove() {
  window_stack_remove(s_window, false);
}