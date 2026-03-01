#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <SDL3/SDL.h>

#include "../include/base.h"
#include "../include/lines.h"

typedef struct {
    f32 x, y, h, w;
}FRect;

void renderRect(SDL_Renderer* renderer, FRect* rect);
void renderFillRect(SDL_Renderer* renderer, FRect* rect);
void rotateRect(FRect* rect, f32 angle);

void renderRect(SDL_Renderer* renderer, FRect* rect){
    f32 h = rect->h;
    f32 w = rect->w;
    f32 x = rect->x;
    f32 y = rect->y;

    renderLine(renderer, x, y, x+w, y);
    renderLine(renderer, x+w, y, x+w, y+h);
    renderLine(renderer, x+w, y+h, x, y+h);
    renderLine(renderer, x, y+h, x, y);
}

void renderFillRect(SDL_Renderer* renderer, FRect* rect){
    i32 h = floor(rect->h);
    i32 w = floor(rect->w);
    i32 x = floor(rect->x);
    i32 y = floor(rect->y);

    for (i32 i = 1; i < h; ++i){
        renderLine(renderer, x+1, y+i, x+w, y+i);
    }
}
