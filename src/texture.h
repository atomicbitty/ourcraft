#ifndef __texture_h__
#define __texture_h__

#include <stdint.h>
#include <stdbool.h>

#include <glad/gl.h>

struct tex2d_image_desc {
  int width, height;
  uint32_t internal_fmt, fmt;
  bool mipmap;
}; 

struct tex2d_desc {
  uint32_t wrap, filter_min, filter_mag; 
}; 

typedef struct texture2d {
  int width, height;
  uint32_t texture;
} texture2d_t;

extern texture2d_t tex2d_create(const struct tex2d_desc *desc);
extern texture2d_t tex2d_create_from_image(const struct tex2d_desc *desc,
  const struct tex2d_image_desc *imgdesc, const void *image);
extern void tex2d_destroy(texture2d_t texture);

extern void tex2d_from_image(texture2d_t texture, const struct tex2d_image_desc *desc, const void *image);

extern void tex2d_bind(texture2d_t texture);
extern void tex2d_unbind(void);

extern void tex2d_set_wrap(uint32_t wrap);
extern void tex2d_set_filter_min(uint32_t filter_min);
extern void tex2d_set_filter_mag(uint32_t filter_mag);

#endif // __texture_h__

