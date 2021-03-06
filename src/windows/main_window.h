#pragma once

#include <pebble.h>

/* Create the window and push to the window stack. */
void main_window_push();

/* Update screen with new steps data. */
void main_window_update_steps(int step_count, int step_goal, int step_average);

/* Pop window from the window stack. */
void main_window_remove();

/* Add movement for liveliness. */
void main_window_breathe();