#ifndef __util_timer_h__
#define __util_timer_h__

// NOTE: The name of the structure is 'tmr' instead of 'timer' because the
// standard library defines a type called 'timer_t'.

#include <stdbool.h>

typedef struct tmr {
  bool running;
  float start;
} tmr_t;

extern tmr_t tmr_create(bool run);

extern void tmr_run(tmr_t *timer);
extern void tmr_stop(tmr_t *timer);
extern float tmr_restart(tmr_t *timer);

extern float tmr_get_elapsed(const tmr_t *timer);

#endif // __util_timer_h__

