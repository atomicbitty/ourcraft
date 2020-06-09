#include "timer.h"

#include <GLFW/glfw3.h>

tmr_t tmr_create(bool run) {
  return (tmr_t) {
    .running = run,
    .start = (float)glfwGetTime()
  };
}

void tmr_run(tmr_t *timer) {
  if(!timer->running) {
    timer->running = true;
    timer->start = (float)glfwGetTime();
  }
}

void tmr_stop(tmr_t *timer) {
  timer->running = false;
}

float tmr_get_elapsed(const tmr_t *timer) {
  return timer->running ? 
    (float)glfwGetTime() - timer->start : 0.0f; 
}

float tmr_restart(tmr_t *timer) {
  float elapsed = tmr_get_elapsed(timer);
  tmr_stop(timer); 
  tmr_run(timer);
  return elapsed;
}


