#pragma once

#include <pebble.h>
#include "comm.h"

/* Load persist data associated with key, and send it. */
void transfer_data(int key);

/* Append new element into persistant array. */
void store_key_data(int key, int element_to_add);