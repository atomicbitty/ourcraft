#ifndef __input_h__
#define __input_h__

#include <stdbool.h>
#include <stdint.h>

#include "table.h"

#define KEY_BUTTON(code) (input_button_t) { BUTTON_TYPE_KEY, code }
#define MOUSE_BUTTON(code) (input_button_t) { BUTTON_TYPE_MOUSE, code }


enum input_button_type {
  BUTTON_TYPE_KEY,
  BUTTON_TYPE_MOUSE
};

typedef struct input_button {
  enum input_button_type type : 4;
  uint16_t code : 12;
} input_button_t;

struct input_state {
  table_t *bind_table;
  bool keys_pressed[256];
  bool keys_pressed_old[256];
  bool mouse_pressed[16];
  bool mouse_pressed_old[16];
  float mouse_x, mouse_y,
      mouse_x_old, mouse_y_old;
  float scroll;
};

extern void input_init(struct input_state *input);
extern void input_cache(struct input_state *input);

extern bool input_key_pressed(struct input_state *input, uint32_t code);
extern bool input_key_triggered(struct input_state *input, uint32_t code);
extern bool input_key_released(struct input_state *input, uint32_t code);
extern bool input_mouse_pressed(struct input_state *input, uint32_t code);
extern bool input_mouse_triggered(struct input_state *input, uint32_t code);
extern bool input_mouse_released(struct input_state *input, uint32_t code);

extern bool input_bind(struct input_state *input,
  const char *name, input_button_t button);
extern bool input_pressed(
  struct input_state *input, const char *name);
extern bool input_triggered(
  struct input_state *input, const char *name);
extern bool input_released(
  struct input_state *input, const char *name);

#endif // __input_h__

