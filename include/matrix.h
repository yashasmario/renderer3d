#pragma once

#include "base.h"

typedef struct {
    f32 x, y;
}vec2f;

typedef struct { 
    f32 x, y, z;
}vec3f;

f32 vec2f_dot(vec2f v1, vec2f v2);
f32 vec2f_cross(vec2f v1, vec2f v2);
f32 vec2f_mag(vec2f v);
vec2f vec2f_unit(vec2f v);
vec2f vec2f_add(vec2f v1, vec2f v2);
vec2f vec2f_sub(vec2f v1, vec2f v2);
