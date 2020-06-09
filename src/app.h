#ifndef __app_h__
#define __app_h__

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdbool.h>

#include "timer.h"
#include "input.h"

struct app_desc {
  const char *title;
  int width;
  int height;
  bool fullscreen;
  bool vsync;
};

typedef struct app {
  GLFWwindow *window;
  GLFWmonitor *monitor;

  struct input_state* input;

  // DO NOT MODIFY THESE!!!
  bool fullscreen;
  bool vsync;
  struct {
    int x;
    int y;
    int width;
    int height;
  } fullscreen_cache;
} app_t;

extern app_t *app_create(const struct app_desc *info);
extern void app_destroy(app_t *app);

extern bool app_set_vsync(app_t *app, bool val);
extern bool app_set_fullscreen(app_t *app, bool val);
extern bool app_toggle_fullscreen(app_t *app);

extern void app_get_display_size(app_t *app, int *w, int *h);
extern float app_get_aspect(app_t *app);

extern bool app_is_open(app_t *app);
extern void app_close(app_t *app);

extern void app_swap_buffers(app_t *app);

#endif

