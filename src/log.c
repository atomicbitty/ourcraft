#include "log.h"

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

static const char *log_type_desc[] = {
  "INFO", "DEBUG", "WARN", "ERROR"
};

void log_print(enum log_type type, const char *where, const char *fmt, ...) {
  printf("%-5s %s: ", log_type_desc[(int)type], where);

  va_list list;
  va_start(list, fmt);
  vprintf(fmt, list);
  va_end(list);

  printf("\n");
}

