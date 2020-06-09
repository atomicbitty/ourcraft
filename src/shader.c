#include "shader.h"
#include "log.h"

#include <glad/gl.h>

#include <stddef.h>

shader_t shader_create(const char *vsrc, const char *fsrc) {
  shader_t shader = { .program = 0 };

  uint32_t vshader = glCreateShader(GL_VERTEX_SHADER);
  uint32_t fshader = glCreateShader(GL_FRAGMENT_SHADER);
 
  glShaderSource(vshader, 1, (const char* const*)&vsrc, NULL);
  glShaderSource(fshader, 1, (const char* const*)&fsrc, NULL);

  int result;
  glCompileShader(vshader);
  glGetShaderiv(vshader, GL_COMPILE_STATUS, &result);
  if(!result) {
    char message[2048] = {0};
    glGetShaderInfoLog(vshader, 2048, NULL, message);

    log_error("shader", "failed to compile vertex shader.\n%s", message);
  }

  glCompileShader(fshader);
  glGetShaderiv(fshader, GL_COMPILE_STATUS, &result);
  if(!result) {
    char message[2048] = {0};
    glGetShaderInfoLog(fshader, 2048, NULL, message);

    log_error("shader", "failed to compile fragment shader.\n%s", message);
  }

  shader.program = glCreateProgram();
  glAttachShader(shader.program, vshader);
  glAttachShader(shader.program, fshader);
  
  glLinkProgram(shader.program);
  glGetProgramiv(shader.program, GL_LINK_STATUS, &result);
  if(!result) {
    char message[2048] = {0};
    glGetProgramInfoLog(shader.program, 2048, NULL, message);

    log_error("shader", "failed to link shader program.\n%s", message);
  }
  
  glDeleteShader(vshader);
  glDeleteShader(fshader);

  return shader;
}

void shader_destroy(shader_t shader) {
  glDeleteProgram(shader.program);
}

void shader_use(shader_t shader) {
  glUseProgram(shader.program);
}

void shader_unuse(void) {
  glUseProgram(0);
}

