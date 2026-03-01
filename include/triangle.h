#pragma once

#include <SDL3/SDL.h>
#include "base.h"
#include "matrix.h"

typedef struct {
    vec2f v1;
    vec2f v2;
    vec2f v3;
}FTriangle;

void renderTriangle(SDL_Renderer *renderer, FTriangle* tri);
void renderFillTriangle(SDL_Renderer *renderer, FTriangle* tri);
