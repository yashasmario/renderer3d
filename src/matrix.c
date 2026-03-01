#include "../include/base.h"
#include "../include/matrix.h"

#include <math.h>

f32 vec2f_dot(vec2f v1, vec2f v2);
f32 vec2f_cross(vec2f v1, vec2f v2);
f32 vec2f_mag(vec2f v);
vec2f vec2f_unit(vec2f v);
vec2f vec2f_add(vec2f v1, vec2f v2);
vec2f vec2f_sub(vec2f v1, vec2f v2);

f32 vec3f_dot(vec3f v1, vec3f v2);
f32 vec3f_mag(vec3f v);
vec3f vec3f_cross(vec3f v1, vec3f v2);
vec3f vec3f_add(vec3f v1, vec3f v2);
vec3f vec3f_sub(vec3f v1, vec3f v2);


f32 vec2f_dot(vec2f v1, vec2f v2){
    return (v1.x * v2.x + v1.y * v2.y);
}
f32 vec2f_cross(vec2f v1, vec2f v2){
    return (v1.x * v2.y - v2.x * v1.y);
}
f32 vec2f_mag(vec2f v){
    return (sqrtf(powf(v.x, 2) + powf(v.y, 2)));
}
vec2f vec2f_add(vec2f v1, vec2f v2){
    return (vec2f) {.x = v1.x + v2.x, .y = v1.y + v2.y};
}
vec2f vec2f_sub(vec2f v1, vec2f v2){
    return (vec2f) {.x = v1.x - v2.x, .y = v1.y - v2.y};
}
vec2f vec2f_unit(vec2f v){
    return (vec2f) {.x = v.x / vec2f_mag(v), .y = v.y / vec2f_mag(v)};
}
