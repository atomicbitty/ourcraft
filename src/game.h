#ifndef __game_h__
#define __game_h__

#include "app.h"
#include "shader.h"
#include "texture.h"
#include <math/vector.h>
#include <math/matrix.h> 

typedef struct gamestate {
  app_t *app;
  uint32_t vbo;
  uint32_t vao;
  float rot;
  vec3 pos;
  vec3 player_pos;
  vec2 player_rot;
  texture2d_t texture;
  shader_t shader;
} gamestate_t;

extern void game_init(gamestate_t *state, app_t *app);
extern void game_quit(gamestate_t *state);

#endif // __game_h__

