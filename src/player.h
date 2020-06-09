#ifndef __player_h__
#define __player_h__

#include "app.h"

#include <math/vector.h>
#include <math/matrix.h>

typedef struct player {
  vec3 position;
  vec2 rotation;
} player_t;

extern void player_update(player_t *player, app_t *app, float dt);
extern void player_get_view_matrix(const player_t *player, mat4 *mat);


#endif // __player_h__
