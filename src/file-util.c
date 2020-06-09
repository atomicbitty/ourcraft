#include "file-util.h"
#include "log.h"

#include <stdlib.h>

char *get_filename_text(const char *filename) {
  FILE* file = fopen(filename, "r");
  if(!file) {
    log_error("file", "failed to open file: %s.", filename);
    return NULL;
  }

  int size;
  char *buf;

  fseek(file, 0, SEEK_END);
  size = ftell(file);
  buf = (char *)calloc(size + 1, sizeof(char));
  fseek(file, 0, SEEK_SET);
  
  if(!buf) {
    log_error("file", "out of memory.");
    return NULL;
  }

  fread(buf, sizeof(char), size, file);
  return buf;
}

char *get_file_text(FILE *file) {
  if(!file) {
    log_error("file", "invalid file stream.");
    return NULL;
  }

  int size;
  char *buf;

  fseek(file, 0, SEEK_END);
  size = ftell(file);
  buf = (char *)calloc(size + 1, sizeof(char));
  fseek(file, 0, SEEK_SET);
  
  if(!buf) {
    log_error("file", "out of memory.");
    return NULL;
  }

  fread(buf, sizeof(char), size, file);
  return buf;
}

