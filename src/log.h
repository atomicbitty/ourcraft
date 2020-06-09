#ifndef __debug_log_h__
#define __debug_log_h__

#define log_info(where, ...) log_print(LOG_INFO, where, __VA_ARGS__)
#define log_debug(where, ...) log_print(LOG_DEBUG, where, __VA_ARGS__)
#define log_warning(where, ...) log_print(LOG_WARNING, where, __VA_ARGS__)
#define log_error(where, ...) log_print(LOG_ERROR, where, __VA_ARGS__)

enum log_type {
  LOG_INFO,
  LOG_DEBUG,
  LOG_WARNING,
  LOG_ERROR
};

extern void log_print(enum log_type type, const char *where, const char *fmt, ...);

#endif // __debug_log_h__

