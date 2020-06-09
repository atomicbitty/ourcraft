#include "game.h"
#include "timer.h"
#include "defs.h"
#include "log.h"
#include "file-util.h"
#include "texture.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math/common.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

static float positions[] = {
  -0.5f, -0.5f, -0.5f,
   0.5f, -0.5f, -0.5f,
   0.5f,  0.5f, -0.5f,
   0.5f,  0.5f, -0.5f,
  -0.5f,  0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,

  -0.5f, -0.5f,  0.5f,
   0.5f, -0.5f,  0.5f,
   0.5f,  0.5f,  0.5f,
   0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,
  -0.5f, -0.5f,  0.5f,

  -0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,
  -0.5f, -0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,

   0.5f,  0.5f,  0.5f,
   0.5f,  0.5f, -0.5f,
   0.5f, -0.5f, -0.5f,
   0.5f, -0.5f, -0.5f,
   0.5f, -0.5f,  0.5f,
   0.5f,  0.5f,  0.5f,

  -0.5f, -0.5f, -0.5f,
   0.5f, -0.5f, -0.5f,
   0.5f, -0.5f,  0.5f,
   0.5f, -0.5f,  0.5f,
  -0.5f, -0.5f,  0.5f,
  -0.5f, -0.5f, -0.5f,

  -0.5f,  0.5f, -0.5f,
   0.5f,  0.5f, -0.5f,
   0.5f,  0.5f,  0.5f,
   0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f, -0.5f,
};

static float texcoords[] = {
   0.0f, 0.0f,
   1.0f, 0.0f,
   1.0f, 1.0f,
   1.0f, 1.0f,
   0.0f, 1.0f,
   0.0f, 0.0f,
              
   0.0f, 0.0f,
   1.0f, 0.0f,
   1.0f, 1.0f,
   1.0f, 1.0f,
   0.0f, 1.0f, 
   0.0f, 0.0f,
              
   1.0f, 0.0f,
   1.0f, 1.0f,
   0.0f, 1.0f,
   0.0f, 1.0f,
   0.0f, 0.0f,
   1.0f, 0.0f,
              
   1.0f, 0.0f,
   1.0f, 1.0f,
   0.0f, 1.0f,
   0.0f, 1.0f,
   0.0f, 0.0f,
   1.0f, 0.0f,
              
   0.0f, 1.0f,
   1.0f, 1.0f,
   1.0f, 0.0f,
   1.0f, 0.0f,
   0.0f, 0.0f,
   0.0f, 1.0f,
              
   0.0f, 1.0f,
   1.0f, 1.0f,
   1.0f, 0.0f,
   1.0f, 0.0f,
   0.0f, 0.0f,
   0.0f, 1.0f
};

void start(gamestate_t *state, app_t *app) {
  input_bind(app->input, "move-forward", KEY_BUTTON(GLFW_KEY_W));
  input_bind(app->input, "move-left", KEY_BUTTON(GLFW_KEY_A));
  input_bind(app->input, "move-right", KEY_BUTTON(GLFW_KEY_D));
  input_bind(app->input, "move-backward", KEY_BUTTON(GLFW_KEY_S));
  input_bind(app->input, "move-up", KEY_BUTTON(GLFW_KEY_SPACE));
  input_bind(app->input, "move-down", KEY_BUTTON(GLFW_KEY_LEFT_SHIFT));
  
  glGenBuffers(1, &state->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, state->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(texcoords), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(texcoords), texcoords);

  size_t offset = 0;
  glGenVertexArrays(1, &state->vao);
  glBindVertexArray(state->vao);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)offset);
  glEnableVertexAttribArray(0);

  offset += sizeof(positions);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)offset);
  glEnableVertexAttribArray(1);
  
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  const char* filename = "../resources/tex.jpg";

  int width, height, channels;
  stbi_uc *image = stbi_load(filename, &width, &height, &channels, STBI_rgb);
  
  if(!image) {
    log_error("texture", "failed to load texture: %s.", filename);
  }
  
  state->texture = tex2d_create_from_image(
    &(struct tex2d_desc) { .wrap = GL_REPEAT, .filter_min = GL_LINEAR_MIPMAP_LINEAR, .filter_mag = GL_LINEAR },
    &(struct tex2d_image_desc) { .width = width, .height = height, .mipmap = true, .internal_fmt = GL_RGB, .fmt = GL_RGB },
    image
  );

  char *vsrc = get_filename_text("../resources/vert.glsl");
  char *fsrc = get_filename_text("../resources/frag.glsl");

  state->shader = shader_create(vsrc, fsrc);
  state->pos = vec3_make(0.0f, 0.0f, -1.0f);
  state->rot = 0.0f;
  state->player_pos = vec3_make(0.0f, 0.0f, 0.0f);
  state->player_rot = vec2_make(0.0f, 0.0f);

  free(vsrc);
  free(fsrc);

  glEnable(GL_DEPTH_TEST);
  glfwSetInputMode(app->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void update(gamestate_t *state, app_t *app, float dt) {
  state->player_rot.y -= 0.2f * (app->input->mouse_x - app->input->mouse_x_old);
  state->player_rot.x += 0.2f * (app->input->mouse_y_old - app->input->mouse_y);

  if(state->player_rot.x >= 89.9f)
    state->player_rot.x = 89.9f;
  if(state->player_rot.x <= -89.9f)
    state->player_rot.x = -89.9f;

  float c = cos(M_DEG_TO_RAD * state->player_rot.y);
  float s = sin(-M_DEG_TO_RAD * state->player_rot.y);
  vec3 dir_front = vec3_make(s, 0.0f, -c);
  vec3 dir_right = vec3_make(c, 0.0f, s);

  log_debug("dir", "[%f, 0, %f]", dir_front.x, dir_front.z);

  if(input_pressed(app->input, "move-forward"))
    state->player_pos = vec3_add(state->player_pos, vec3_mul(dir_front, dt));
  if(input_pressed(app->input, "move-backward"))
    state->player_pos = vec3_sub(state->player_pos, vec3_mul(dir_front, dt));
  if(input_pressed(app->input, "move-right"))
    state->player_pos = vec3_add(state->player_pos, vec3_mul(dir_right, dt));
  if(input_pressed(app->input, "move-left"))
    state->player_pos = vec3_sub(state->player_pos, vec3_mul(dir_right, dt));
  if(input_pressed(app->input, "move-up"))
    state->player_pos.y += dt;
  if(input_pressed(app->input, "move-down"))
    state->player_pos.y -= dt;
  
  //state->pos.x += 0.5f * dt;
  //state->rot += 0.5f * dt;
}

void render(gamestate_t *state, app_t *app, float dt) {
  (void)dt;
  glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  float aspect = app_get_aspect(app);

  mat4 view;
  mat_camera(&view, state->player_pos, state->player_rot);
  
  mat4 projection;
  mat_perspective(&projection, 90.0f, aspect, 0.01f, 1000.0f);

  mat4 model;
  mat_translate(&model, NULL, state->pos);
  mat_rotate_euler(&model, &model, vec3_make(0.0f, 50 * state->rot, 0.0f)); 

  tex2d_bind(state->texture);
  shader_use(state->shader);
  glUniformMatrix4fv(glGetUniformLocation(state->shader.program, "u_view"), 1, true, view.data);
  glUniformMatrix4fv(glGetUniformLocation(state->shader.program, "u_model"), 1, true, model.data);
  glUniformMatrix4fv(glGetUniformLocation(state->shader.program, "u_projection"), 1, true, projection.data);
  glBindVertexArray(state->vao);
  glDrawArrays(GL_TRIANGLES, 0, 36);
}

void game_init(gamestate_t *state, app_t *app) {
  tmr_t timer = tmr_create(true);

  start(state, app);

  while (app_is_open(app)) {
    float dt = tmr_restart(&timer);
    
    glfwPollEvents();
    
    update(state, app, dt);
    render(state, app, dt);
    app_swap_buffers(app);
    
    input_cache(app->input);
  }
}

void game_quit(gamestate_t *state) {
  (void)state;  
}

