#include "app.h"

#include <stdlib.h>
#include <assert.h>

#include "log.h"
#include "defs.h"


static void error_callback(int code, const char *str) {
  UNUSED(code);
  log_error("glfw", str);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  UNUSED(key);
  UNUSED(mods);
  app_t *app = (app_t *)glfwGetWindowUserPointer(window);
  app->input->keys_pressed[scancode] = action != GLFW_RELEASE;
}

static void mouse_callback(GLFWwindow *window, int button, int action, int mods) {
  UNUSED(mods);
  app_t *app = (app_t *)glfwGetWindowUserPointer(window);
  app->input->mouse_pressed[button] = action != GLFW_RELEASE;
}

static void cursor_callback(GLFWwindow *window, double x, double y) {
  app_t *app = (app_t *)glfwGetWindowUserPointer(window);
  app->input->mouse_x = (float)x;
  app->input->mouse_y = (float)y;
}

static void scroll_callback(GLFWwindow *window, double x, double y) {
  UNUSED(x);
  app_t *app = (app_t *)glfwGetWindowUserPointer(window);
  app->input->scroll = (float)y;
}

static void resize_callback(GLFWwindow *window, int width, int height) {
  UNUSED(window);
  glViewport(0, 0, (float)width, (float)height);
}

static bool init_libs(void) {
  if(!glfwInit()) {
    log_error("glfw", "failed to initialize.");
    return false;
  }
  glfwSetErrorCallback(error_callback);
  return true;
}

static bool init_input(app_t *app) {
  app->input = (struct input_state *)calloc(1, sizeof(struct input_state));
  input_init(app->input);

  glfwSetWindowSizeCallback(app->window, resize_callback);
  glfwSetKeyCallback(app->window, key_callback);
  glfwSetMouseButtonCallback(app->window, mouse_callback);
  glfwSetCursorPosCallback(app->window, cursor_callback);
  glfwSetScrollCallback(app->window, scroll_callback);
  return true;
}


static void load_gl(app_t *app) {
  glfwMakeContextCurrent(app->window);
  if(!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
    log_error("opengl", "failed to load opengl functions.");
  }
}

static void quit_libs(void) {
  glfwTerminate();
}

app_t *app_create(const struct app_desc *info) {
  if(!init_libs())
    return NULL;

  assert(info != NULL);

  app_t *app = (app_t *)calloc(1, sizeof(app_t));

  if(app == NULL) {
    log_error("app", "failed to create application, out of memory.");
    return NULL;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  int width = info->width, height = info->height;
  GLFWmonitor *usedmonitor = NULL;

  app->monitor = glfwGetPrimaryMonitor();
  if(info->fullscreen) {
    const GLFWvidmode *videomode = glfwGetVideoMode(app->monitor);
    width = videomode->width;
    height = videomode->height;
    usedmonitor = app->monitor;

    app->fullscreen_cache.x = 30;
    app->fullscreen_cache.y = 30;
    app->fullscreen_cache.width = info->width;
    app->fullscreen_cache.height = info->height;

    app->fullscreen = true;
  }

  app->window = glfwCreateWindow(width, height, info->title, usedmonitor, NULL);
  if(app->window == NULL) {
    free(app);
    quit_libs();
    return NULL;
  }
  
  glfwSetWindowUserPointer(app->window, app);

  init_input(app);
  load_gl(app);

  if(info->vsync)
    glfwSwapInterval(1);
  else 
    glfwSwapInterval(0);

  log_info("app", "application has been successfully created!");
  return app;
}

void app_destroy(app_t *app) {
  assert(app != NULL);

  quit_libs();
  free(app->input);
  free(app);

  log_info("app", "bye bye!");
}

bool app_set_vsync(app_t *app, bool val) {
  assert(app != NULL);

  glfwSwapInterval(val ? 1 : 0);
  return val;
}

bool app_set_fullscreen(app_t *app, bool fullscreen) {
  assert(app != NULL);

  if (fullscreen) {
    if (app->fullscreen)
      return true;

    const GLFWvidmode *videomode = glfwGetVideoMode(app->monitor);

    glfwGetWindowSize(app->window, &app->fullscreen_cache.width, &app->fullscreen_cache.height);
    glfwGetWindowPos(app->window, &app->fullscreen_cache.x, &app->fullscreen_cache.y);

    glfwSetWindowMonitor(app->window, app->monitor, 0, 0, 
      videomode->width, videomode->height, videomode->refreshRate);

    app->fullscreen = true;
  }
  else {
    glfwSetWindowMonitor(app->window, NULL,
	  app->fullscreen_cache.x, app->fullscreen_cache.y,
      app->fullscreen_cache.width, app->fullscreen_cache.height, 0);

    app->fullscreen = false;
  }

  return app->fullscreen; 
}

bool app_toggle_fullscreen(app_t *app) {
  assert(app != NULL);
  
  return app_set_fullscreen(app, !app->fullscreen);
}

void app_get_display_size(app_t *app, int *w, int *h) {
  assert(app != NULL);

  glfwGetWindowSize(app->window, w, h);
}

float app_get_aspect(app_t *app) {
  assert(app != NULL);

  int width = 0, height = 0;
  glfwGetWindowSize(app->window, &width, &height);

  return (float)width / height;
}

bool app_is_open(app_t *app) {
  assert(app != NULL);

  return !glfwWindowShouldClose(app->window);
}

void app_close(app_t *app) {
  assert(app != NULL);

  glfwSetWindowShouldClose(app->window, false);
}

void app_swap_buffers(app_t *app) {
  assert(app != NULL);

  glfwSwapBuffers(app->window);
}

