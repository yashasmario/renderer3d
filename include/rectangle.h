#pragma once

#include "base.h"
#include <SDL3/SDL.h>

typedef struct {
    f32 x, y, w, h;
}FRect;

void renderRect(SDL_Renderer* renderer, FRect* rect);
void renderFillRect(SDL_Renderer* renderer, FRect* rect);
