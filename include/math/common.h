#ifndef __math_common_h__
#define __math_common_h__

#ifndef M_PI
#define M_PI 3.14159265359
#endif // M_PI

#ifndef M_RAD_TO_DEG
#define M_RAD_TO_DEG (180.0 / M_PI)
#endif // RAD_TO_DEG

#ifndef M_DEG_TO_RAD
#define M_DEG_TO_RAD (M_PI / 180.0)
#endif //DEG_TO_RAD

inline float fminf_fast(float x, float y) {
    return x > y ? y : x;
}

inline float fmaxf_fast(float x, float y) {
    return x > y ? x : y;
}

inline float clamp(float x, float mn, float mx) {
    return fmaxf_fast(mn, fminf_fast(mx, x));
}


#endif // __math_common_h__
