#include "input.h"

#include <string.h>

#include <GLFW/glfw3.h>

static uintptr_t button_to_uptr(input_button_t button) {
  return *(uintptr_t *)&button;
}

static input_button_t uptr_to_button(uintptr_t code) {
  uintptr_t cd = code;
  return *(input_button_t *)&cd;
}

void input_init(struct input_state *input) {
  memset(input->keys_pressed, 0, sizeof(input->keys_pressed));
  memset(input->keys_pressed_old, 0, sizeof(input->keys_pressed));
  memset(input->mouse_pressed, 0, sizeof(input->mouse_pressed));
  memset(input->mouse_pressed_old, 0, sizeof(input->mouse_pressed_old));
  input->mouse_x = 0.0f;
  input->mouse_y = 0.0f;
  input->mouse_x_old = 0.0f;
  input->mouse_y_old = 0.0f;
  
  input->bind_table = table_create(256);
}

void input_cache(struct input_state *input) {
  memcpy(input->keys_pressed_old, input->keys_pressed,
    sizeof(input->keys_pressed_old));
  memcpy(input->mouse_pressed_old, input->mouse_pressed,
    sizeof(input->mouse_pressed_old));
  input->mouse_x_old = input->mouse_x;
  input->mouse_y_old = input->mouse_y;
}

bool input_key_pressed(struct input_state *input, uint32_t code) {
  return input->keys_pressed[glfwGetKeyScancode(code)];
}
  
bool input_key_triggered(struct input_state *input, uint32_t code) {
  return input->keys_pressed[glfwGetKeyScancode(code)] &&
        !input->keys_pressed_old[glfwGetKeyScancode(code)];
}

bool input_key_released(struct input_state *input, uint32_t code) {
  return !input->keys_pressed[glfwGetKeyScancode(code)] &&
          input->keys_pressed_old[glfwGetKeyScancode(code)];
}

bool input_mouse_pressed(struct input_state *input, uint32_t code) {
  return input->mouse_pressed[code];
}

bool input_mouse_triggered(struct input_state *input, uint32_t code) {
  return input->mouse_pressed[code] && !input->mouse_pressed_old[code];
}

bool input_mouse_released(
  struct input_state *input, uint32_t code) {
  return !input->mouse_pressed[code] && input->mouse_pressed_old[code];
}

extern bool input_bind(struct input_state *input,
  const char *name, input_button_t button) {
  table_set(input->bind_table, name, 
    /*i know this is not a good practice, but it's the fastest solution.*/ 
    (void*)button_to_uptr(button));
  return true;
}

extern bool input_pressed(
  struct input_state *input, const char *name) {
  input_button_t btn = 
    uptr_to_button((uintptr_t)table_get(input->bind_table, name));
  
  switch (btn.type)
  {
  case BUTTON_TYPE_KEY:
    return input->keys_pressed[glfwGetKeyScancode(btn.code)];
  case BUTTON_TYPE_MOUSE:
    return input->mouse_pressed[btn.code];
  default:
    return false;
  }
}

extern bool input_triggered(
  struct input_state *input, const char *name) {
  input_button_t btn = 
    uptr_to_button((uintptr_t)table_get(input->bind_table, name));
  
  switch (btn.type)
  {
  case BUTTON_TYPE_KEY:
    return input->keys_pressed[glfwGetKeyScancode(btn.code)] &&
          !input->keys_pressed_old[glfwGetKeyScancode(btn.code)];
  case BUTTON_TYPE_MOUSE:
    return input->mouse_pressed[btn.code] &&
          !input->mouse_pressed_old[btn.code];
  default:
    return false;
  }
}

extern bool input_released(
  struct input_state *input, const char *name) {
  input_button_t btn = 
    uptr_to_button((uintptr_t)table_get(input->bind_table, name));
  
  switch (btn.type)
  {
  case BUTTON_TYPE_KEY:
    return !input->keys_pressed[glfwGetKeyScancode(btn.code)] &&
           input->keys_pressed_old[glfwGetKeyScancode(btn.code)];
  case BUTTON_TYPE_MOUSE:
    return !input->mouse_pressed[btn.code] &&
            input->mouse_pressed_old[btn.code];
  default:
    return false;
  }
}

