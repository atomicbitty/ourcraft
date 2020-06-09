#ifndef __math_matrix_h__
#define __math_matrix_h__

#include "vector.h"
#include "common.h"
#include <string.h>

typedef struct mat4 {
	float data[4 * 4];
} mat4;

static const float __identity[] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f 
};

static inline void mat4_make(mat4 *mat, const float *f) {
	memcpy(mat->data, f, 16 * sizeof(float));
}

static inline void mat4_identity(mat4 *mat) {
	memcpy(mat->data, __identity, 16 * sizeof(float));
}

static inline void mat4_copy(mat4 *dest, const mat4 *src) {
	memcpy(dest->data, src->data, 16 * sizeof(float));
}

static void mat4_inverse(mat4 *dest, const mat4 *src) {
	const float *m = src->data;

	float A2323 = m[10] * m[15] - m[11] * m[14];
	float A1323 = m[9] * m[15] - m[11] * m[13];
	float A1223 = m[9] * m[14] - m[10] * m[13];
	float A0323 = m[8] * m[15] - m[11] * m[12];
	float A0223 = m[8] * m[14] - m[10] * m[12];
	float A0123 = m[8] * m[13] - m[9] * m[12];
	float A2313 = m[6] * m[15] - m[7] * m[14];
	float A1313 = m[5] * m[15] - m[7] * m[13];
	float A1213 = m[5] * m[14] - m[6] * m[13];
	float A2312 = m[6] * m[11] - m[7] * m[10];
	float A1312 = m[5] * m[11] - m[7] * m[9];
	float A1212 = m[5] * m[10] - m[6] * m[9];
	float A0313 = m[4] * m[15] - m[7] * m[12];
	float A0213 = m[4] * m[14] - m[6] * m[12];
	float A0312 = m[4] * m[11] - m[7] * m[8];
	float A0212 = m[4] * m[10] - m[6] * m[8];
	float A0113 = m[4] * m[13] - m[5] * m[12];
	float A0112 = m[4] * m[9] - m[5] * m[8];

	float det = m[0] * (m[5] * A2323 - m[6] * A1323 + m[7] * A1223)
				- m[1] * (m[4] * A2323 - m[6] * A0323 + m[7] * A0223)
				+ m[2] * (m[4] * A1323 - m[5] * A0323 + m[7] * A0123)
				- m[3] * (m[4] * A1223 - m[5] * A0223 + m[6] * A0123);
	det = 1.0f / det;

	
	mat4 mat;

	mat.data[0] = det * (m[5] * A2323 - m[6] * A1323 + m[7] * A1223);
	mat.data[1] = det * -(m[1] * A2323 - m[2] * A1323 + m[3] * A1223);
	mat.data[2] = det * (m[1] * A2313 - m[2] * A1313 + m[3] * A1213);
	mat.data[3] = det * -(m[1] * A2312 - m[2] * A1312 + m[3] * A1212);
	mat.data[4] = det * -(m[4] * A2323 - m[6] * A0323 + m[7] * A0223);
	mat.data[5] = det * (m[0] * A2323 - m[2] * A0323 + m[3] * A0223);
	mat.data[6] = det * -(m[0] * A2313 - m[2] * A0313 + m[3] * A0213);
	mat.data[7] = det * (m[0] * A2312 - m[2] * A0312 + m[3] * A0212);
	mat.data[8] = det * (m[4] * A1323 - m[5] * A0323 + m[7] * A0123);
	mat.data[9] = det * -(m[0] * A1323 - m[1] * A0323 + m[3] * A0123);
	mat.data[10] = det * (m[0] * A1313 - m[1] * A0313 + m[3] * A0113);
	mat.data[11] = det * -(m[0] * A1312 - m[1] * A0312 + m[3] * A0112);
	mat.data[12] = det * -(m[4] * A1223 - m[5] * A0223 + m[6] * A0123);
	mat.data[13] = det * (m[0] * A1223 - m[1] * A0223 + m[2] * A0123);
	mat.data[14] = det * -(m[0] * A1213 - m[1] * A0213 + m[2] * A0113);
	mat.data[15] = det * (m[0] * A1212 - m[1] * A0212 + m[2] * A0112);

	mat4_copy(dest, &mat);


}

static inline void mat4_transpose(mat4 *dest, const mat4 *src) {
	dest->data[0] = src->data[0];
	dest->data[1] = src->data[4];
	dest->data[2] = src->data[8];
	dest->data[3] = src->data[12];
	dest->data[4] = src->data[1];
	dest->data[5] = src->data[5];
	dest->data[6] = src->data[9];
	dest->data[7] = src->data[13];
	dest->data[8] = src->data[2];
	dest->data[9] = src->data[6];
	dest->data[10] = src->data[10];
	dest->data[11] = src->data[14];
	dest->data[12] = src->data[3];
	dest->data[13] = src->data[7];
	dest->data[14] = src->data[10];
	dest->data[15] = src->data[15];
}

static inline void mat4_mul(mat4 *dest, const mat4 *src1, const mat4 *src2) {
	mat4 result;
	float *d = result.data;
	const float *a = src1->data;
	const float *b = src2->data;

	d[0] = a[0] * b[0] + a[1] * b[4] + a[2] * b[8] +  a[3] * b[12];
	d[1] = a[0] * b[1] + a[1] * b[5] + a[2] * b[9] +  a[3] * b[13];
	d[2] = a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14];
	d[3] = a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15];
	d[4] = a[4] * b[0] + a[5] * b[4] + a[6] * b[8] +  a[7] * b[12];
	d[5] = a[4] * b[1] + a[5] * b[5] + a[6] * b[9] +  a[7] * b[13];
	d[6] = a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14];
	d[7] = a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15];
	d[8] = a[8] * b[0] + a[9] * b[4] + a[10] * b[8] +  a[11] * b[12];
	d[9] = a[8] * b[1] + a[9] * b[5] + a[10] * b[9] +  a[11] * b[13];
	d[10] = a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14];
	d[11] = a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15];
	d[12] = a[12] * b[0] + a[13] * b[4] + a[14] * b[8] +  a[15] * b[12];
	d[13] = a[12] * b[1] + a[13] * b[5] + a[14] * b[9] +  a[15] * b[13];
	d[14] = a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14];
	d[15] = a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15];

	mat4_copy(dest, &result);
}

static inline void mat4_mulf(mat4 *dest, const mat4 *src1, float f)
{
	dest->data[0] = src1->data[0] * f;
	dest->data[1] = src1->data[1] * f;
	dest->data[2] = src1->data[2] * f;
	dest->data[3] = src1->data[3] * f;
	dest->data[4] = src1->data[4] * f;
	dest->data[5] = src1->data[5] * f;
	dest->data[6] = src1->data[6] * f;
	dest->data[7] = src1->data[7] * f;
	dest->data[8] = src1->data[8] * f;
	dest->data[9] = src1->data[9] * f;
	dest->data[10] = src1->data[10] * f;
	dest->data[11] = src1->data[11] * f;
	dest->data[12] = src1->data[12] * f;
	dest->data[13] = src1->data[13] * f;
	dest->data[14] = src1->data[14] * f;
	dest->data[15] = src1->data[15] * f;
}

static inline vec4 mat4_mulv(const mat4 *mat, vec4 vec) {
	vec4 result = {
		mat->data[0] * vec.x + mat->data[1] * vec.y + mat->data[2] * vec.z + mat->data[3] * vec.w,
		mat->data[4] * vec.x + mat->data[5] * vec.y + mat->data[6] * vec.z + mat->data[7] * vec.w,
		mat->data[8] * vec.x + mat->data[9] * vec.y + mat->data[10] * vec.z + mat->data[11] * vec.w,
		mat->data[12] * vec.x + mat->data[13] * vec.y + mat->data[14] * vec.z + mat->data[15] * vec.w };

	return result;
}

static inline float mat4_get(const mat4 *mat, int row, int column) {
	return mat->data[4 * row + column];
}

static inline void mat4_set(mat4 *mat, float value, int row, int column) {
	mat->data[4 * row + column] = value;
}

static inline void mat_perspective(mat4 *mat, float fov, float aspect, float near, float far) {
	memset(mat->data, 0, 16 * sizeof(float));

	if (aspect == 0.0f) return;

	const float tan_half_fov = tanf(fov * M_DEG_TO_RAD * 0.5f);
	const float inv_fn = 1.0f / (far - near);

	mat->data[0] = 1.0f / (aspect * tan_half_fov);
	mat->data[5] = 1.0f / tan_half_fov;
	mat->data[10] = -(far + near) * inv_fn;
	mat->data[11] = -2.0f * near * far * inv_fn;
	mat->data[14] = -1.0f;
}

static inline void mat_ortho(mat4 *mat, float left, float right, float bottom, float top,
	float near, float far) {
	memset(mat->data, 0, 16 * sizeof(float));
	
	mat->data[0] = 2.0f / (right - left);
	mat->data[5] = 2.0f / (top - bottom);
	mat->data[10] = -2.0f / (far - near);
	mat->data[3] = -(right + left) / (right - left);
	mat->data[7] = -(top + bottom) / (top - bottom);
	mat->data[11] = -(far + near) / (far - near);
	mat->data[15] = 1.0f;
}

static inline void mat_rotate_euler_yx(mat4 *dest, const mat4 *src, vec2 v) {
	v.x *= M_DEG_TO_RAD; v.y *= M_DEG_TO_RAD;

	//cosines and sines of the angles
	float cx = cosf(v.x), cy = cosf(v.y),
		sx = sinf(v.x), sy = sinf(v.y);

	mat4 rot;
	float *r = rot.data;

	r[0] = cy;   r[1] = sx * sy; r[2] = sy * cx; r[3] = 0.0f;
	r[4] = 0.0f; r[5] = cx;	r[6] = -sx; r[7] = 0.0f;
	r[8] = -sy;  r[9] = cy * sx; r[10] = cy * cx; r[11] = 0.0f;
	r[12] = 0.0f; r[13] = 0.0f; r[14] = 0.0f; r[15] = 1.0f;

	mat4_mul(dest, src ? src : (const mat4*)__identity, &rot);
}

static inline void mat_translate(mat4 *dest, const mat4 *src, vec3 v) {
	float *m = dest->data;
	const float *s = src ? src->data : __identity;

	m[0] = s[0];
	m[1] = s[1];
	m[2] = s[2];
	m[3] = s[0] * v.x + s[1] * v.y + s[2] * v.z + s[3];
	m[4] = s[4];
	m[5] = s[5];
	m[6] = s[6];
	m[7] = s[4] * v.x + s[5] * v.y + s[6] * v.z + s[7];
	m[8] = s[8];
	m[9] = s[9];
	m[10] = s[10];
	m[11] = s[8] * v.x + s[9] * v.y + s[10] * v.z + s[11];
	m[12] = s[12];
	m[13] = s[13];
	m[14] = s[14];
	m[15] = s[12] * v.x + s[13] * v.y + s[14] * v.z + s[15];
}

static inline void mat_rotate_euler(mat4 *dest, const mat4 *src, vec3 v) {
	v.x *= M_DEG_TO_RAD; v.y *= M_DEG_TO_RAD; v.z *= M_DEG_TO_RAD;

	//cosines and sines of the angles
	float cx = cosf(v.x), cy = cosf(v.y), cz = cosf(v.z),
		sx = sinf(v.x), sy = sinf(v.y), sz = sinf(v.z);

	mat4 rot;
	float *r = rot.data;

	r[0] = cz * cy; r[1] = cz * sy * sx - sz * cx; r[2] = sx * sz + cz * sy * cx; r[3] = 0.0f;
	r[4] = sz * cy; r[5] = cx * cz + sz * sy * sx; r[6] = cx * sz * sy - sx * cz; r[7] = 0.0f;
	r[8] = -sy; r[9] = cy * sx; r[10] = cy * cx; r[11] = 0.0f;
	r[12] = 0.0f; r[13] = 0.0f; r[14] = 0.0f; r[15] = 1.0f;

	mat4_mul(dest, src ? src : (const mat4*)__identity, &rot);
}

static inline void mat_scale(mat4 *dest, const mat4 *src, vec3 v) {
	if (!src)
		src = (const mat4*)__identity;

	float *m = dest->data;
	const float *s = src->data;

	m[0] = s[0] * v.x;
	m[1] = s[1] * v.y;
	m[2] = s[2] * v.z;
	m[3] = s[3];
	m[4] = s[4] * v.x;
	m[5] = s[5] * v.y;
	m[6] = s[6] * v.z;
	m[7] = s[7];
	m[8] = s[8] * v.x;
	m[9] = s[9] * v.y;
	m[10] = s[10] * v.z;
	m[11] = s[11];
	m[12] = s[12] * v.x;
	m[13] = s[13] * v.y;
	m[14] = s[14] * v.z;
	m[15] = s[15];
}

static inline void mat_camera(mat4 *dest, vec3 pos, vec2 rot) {
	if (!dest) return;
	
	rot.x *= M_DEG_TO_RAD; rot.y *= M_DEG_TO_RAD;

	//cosines and sines of the angles
	float cx = cosf(rot.x), cy = cosf(rot.y),
		sx = sinf(rot.x), sy = sinf(rot.y);

	float *r = dest->data;

	r[0] = cy;   r[1] = sx * sy; r[2] = sy * cx; r[3] = pos.x;
	r[4] = 0.0f; r[5] = cx;	r[6] = -sx; r[7] = pos.y;
	r[8] = -sy;  r[9] = cy * sx; r[10] = cy * cx; r[11] = pos.z;
	r[12] = 0.0f; r[13] = 0.0f; r[14] = 0.0f; r[15] = 1.0f;

	mat4_inverse(dest, dest);
}


#endif //__math_matrix_h__
