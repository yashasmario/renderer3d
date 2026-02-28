// Implementing the bresenham's line algorithm to understand 
// how lines are drawn onto the screen
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/base.h"
#include "../include/lines.h"

#include <SDL3/SDL.h>

void renderLine_low(SDL_Renderer* renderer, f32 x1, f32 y1, f32 x2, f32 y2){
    f32 dx = x2 - x1;
    f32 dy = y2 - y1;

    f32 yi = 1;
    if (dy < 0){
        yi = -1;
        dy = -dy;
    }
    
    f32 D = (2*dy)-dx;
    f32 y = y1;

    for (f32 x = x1; x < x2; x++){
        SDL_RenderPoint(renderer, x, y);
        if ( D > 0 ){
            y += yi;
            D += 2*(dy - dx);
        }else{
            D += 2*dy;
        }
    }
}

void renderLine_high(SDL_Renderer* renderer, f32 x1, f32 y1, f32 x2, f32 y2){
    f32 dx = x2 - x1;
    f32 dy = y2 - y1;

    f32 xi = 1;
    if (dx < 0){
        xi = -1;
        dx = -dx;
    }
    
    f32 D = (2*dx)-dy;
    f32 x = x1;

    for (f32 y = y1; y < y2; y++){
        SDL_RenderPoint(renderer, x, y);
        if ( D > 0 ){
            x += xi;
            D += 2*(dx - dy);
        }else{
            D += 2*dx;
        }
    }
}

void renderLine(SDL_Renderer* renderer, f32 x1, f32 y1, f32 x2, f32 y2){
    if ( fabsf(y2 - y1) < fabsf(x2 - x1)){
        if ( x1 > x2) renderLine_low(renderer, x2, y2, x1, y1);
        else renderLine_low(renderer, x1, y1, x2, y2);
    }else {
        if (y1 > y2) renderLine_high(renderer, x2, y2, x1, y1);
        else renderLine_high(renderer, x1, y1, x2, y2);
    }
}
