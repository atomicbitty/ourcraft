#ifndef __shader_h__
#define __shader_h__

#include <glad/gl.h>
#include <stdint.h>

typedef struct shader {
  uint32_t program;
} shader_t;

extern shader_t shader_create(const char* vsrc, const char* fsrc);
extern void shader_destroy(shader_t shader);

extern void shader_use(shader_t shader);
extern void shader_unuse(void);

#endif // __shader_h__ 

