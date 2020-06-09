#ifndef __math_vector_h__
#define __math_vector_h__

#include <math.h>

typedef struct vec2 {
	float x, y;
} vec2;

typedef struct vec3 {
	float x, y, z;
} vec3;

typedef struct vec4 {
	float x, y, z, w;
} vec4;


static inline vec2 vec2_make(float x, float y) {
	vec2 v = { x, y }; return v;
}

static inline vec2 vec2_add(vec2 a, vec2 b) {
	vec2 v = { a.x + b.x, a.y + b.y }; return v;
}

static inline vec2 vec2_sub(vec2 a, vec2 b) {
	vec2 v = { a.x - b.x, a.y - b.y }; return v;
}

static inline vec2 vec2_mul(vec2 a, float b) {
	vec2 v = { a.x * b, a.y * b }; return v;
}

static inline vec2 vec2_div(vec2 a, float b) {
	float inv = 1.0f / b;
	vec2 v = { a.x * inv, a.y * inv }; return v;
}

static inline float vec2_length(vec2 v) {
	return sqrtf(v.x * v.x + v.y * v.y);
}

static inline float vec2_sqlength(vec2 v) {
	return v.x * v.x + v.y * v.y;
}

static inline float vec2_dot(vec2 a, vec2 b) {
	return a.x * b.x + a.y * b.y;
}

static inline float vec2_sqdistance(vec2 a, vec2 b)
{
	vec2 diff = { a.x - b.x, a.y - b.y };
	return diff.x * diff.x + diff.y * diff.y;
}

static inline float vec2_distance(vec2 a, vec2 b) {
	vec2 diff = { a.x - b.x, a.y - b.y };
	return sqrtf(diff.x * diff.x + diff.y * diff.y);
}

static inline vec2 vec2_normalize(vec2 v) {
	float sqlen = v.x * v.x + v.y * v.y;
	if (sqlen < 0.000001f)
		return vec2_make(0.0f, 0.0f);
	float invlen = 1.0f / sqrtf(sqlen);
	vec2 result = { invlen * v.x, invlen * v.y };
	return result;
}

static inline vec3 vec3_make(float x, float y, float z) {
	vec3 v = { x, y, z }; return v;
}

static inline vec3 vec3_add(vec3 a, vec3 b) {
	vec3 v = { a.x + b.x, a.y + b.y, a.z + b.z }; return v;
}

static inline vec3 vec3_sub(vec3 a, vec3 b) {
	vec3 v = { a.x - b.x, a.y - b.y, a.z - b.z }; return v;
}

static inline vec3 vec3_mul(vec3 a, float b) {
	vec3 v = { a.x * b, a.y * b, a.z * b }; return v;
}

static inline vec3 vec3_div(vec3 a, float b) {
	float inv = 1.0f / b;
	vec3 v = { a.x * inv, a.y * inv, a.z * inv }; return v;
}

static inline float vec3_length(vec3 v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

static inline float vec3_sqlength(vec3 v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

static inline float vec3_dot(vec3 a, vec3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline float vec3_sqdistance(vec3 a, vec3 b)
{
	vec3 diff = { a.x - b.x, a.y - b.y, a.z - b.z };
	return diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
}

static inline float vec3_distance(vec3 a, vec3 b) {
	vec3 diff = { a.x - b.x, a.y - b.y, a.z - b.z };
	return sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
}

static inline vec3 vec3_normalize(vec3 v) {
	float sqlen = v.x * v.x + v.y * v.y + v.z * v.z;
	if (sqlen < 0.000001f)
		return vec3_make(0.0f, 0.0f, 0.0f);
	float invlen = 1.0f / sqrtf(sqlen);
	vec3 result = { invlen * v.x, invlen * v.y, invlen * v.z };
	return result;
}

static inline vec4 vec4_make(float x, float y, float z, float w) {
	vec4 v = { x, y, z, w }; return v;
}

static inline vec4 vec4_add(vec4 a, vec4 b) {
	vec4 v = { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w }; return v;
}

static inline vec4 vec4_sub(vec4 a, vec4 b) {
	vec4 v = { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w }; return v;
}

static inline vec4 vec4_mul(vec4 a, float b) {
	vec4 v = { a.x * b, a.y * b, a.z * b, a.w * b }; return v;
}

static inline vec4 vec4_div(vec4 a, float b) {
	float inv = 1.0f / b;
	vec4 v = { a.x * inv, a.y * inv, a.z * inv, a.w * inv }; return v;
}



#endif // __math_vector_h__
