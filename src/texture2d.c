#include "texture.h"

texture2d_t tex2d_create(const struct tex2d_desc* desc) {
  texture2d_t tex = {0};
  glGenTextures(1, &tex.texture);
  glBindTexture(GL_TEXTURE_2D, tex.texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, desc->wrap);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, desc->wrap);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, desc->filter_min);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, desc->filter_mag);

  glBindTexture(GL_TEXTURE_2D, 0);

  return tex;
}

texture2d_t tex2d_create_from_image(const struct tex2d_desc* desc,
    const struct tex2d_image_desc *imgdesc, const void *image) {
  texture2d_t tex = tex2d_create(desc);
  tex2d_from_image(tex, imgdesc, image);

  return tex;
}

void tex2d_destroy(texture2d_t texture) {
  if(texture.texture)
    glDeleteTextures(1, &texture.texture);
}

void tex2d_from_image(texture2d_t texture, const struct tex2d_image_desc *desc, const void *image) {
  glBindTexture(GL_TEXTURE_2D, texture.texture);
  glTexImage2D(GL_TEXTURE_2D, 0, desc->internal_fmt, desc->width, desc->height, 0, desc->fmt, GL_UNSIGNED_BYTE, image);

  if(desc->mipmap)
    glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);
}

void tex2d_bind(texture2d_t texture) {
  glBindTexture(GL_TEXTURE_2D, texture.texture);
}

void tex2d_unbind(void) {
  glBindTexture(GL_TEXTURE_2D, 0);
}

void tex2d_set_wrap(uint32_t wrap) {
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
}

void tex2d_set_filter_min(uint32_t filter_min) {
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min);
}

void tex2d_set_filter_mag(uint32_t filter_mag) {
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_mag);
}

