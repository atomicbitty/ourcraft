#include "app.h"
#include "game.h"

int main() {
  struct app_desc desc = {
    .title = "ourcraft",
    .width = 1280,
    .height = 720,
    .vsync = true,
    .fullscreen = false
  };
  
  app_t      *app = app_create(&desc);
  gamestate_t state;

  game_init(&state, app);
  game_quit(&state);
  app_destroy(app);

  return 0;
}

