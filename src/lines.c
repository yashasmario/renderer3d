// Implementing the bresenham's line algorithm to understand 
// how lines are drawn onto the screen
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SDL3/SDL.h>

typedef uint8_t u8 ;
typedef uint16_t u16 ;
typedef uint32_t u32 ;
typedef uint64_t u64 ;
typedef int8_t i8 ;
typedef int16_t i16 ;
typedef int32_t i32 ;
typedef int64_t i64 ;

typedef float f32 ;
typedef double d64 ;

typedef struct {
    f32 x, y;
}vec2f;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

bool running = true;

void renderLine(SDL_Renderer* renderer, vec2f p1, vec2f p2);

int main(void){
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    
    SDL_WindowID WINDOW_ID;

    SDL_CreateWindowAndRenderer("lines", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_MOUSE_FOCUS, &window, &renderer);
    if (window == NULL || renderer == NULL){
        SDL_Log("Failed to create window or renderer: %s", SDL_GetError());
    }

    SDL_Event event;
    while (running){

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);


        vec2f p1 = {.x = 0, .y = 0};
        vec2f p2 = {.x = WINDOW_WIDTH, .y = 0};
        vec2f p3 = {.x = WINDOW_WIDTH, .y = WINDOW_HEIGHT};
        vec2f p4 = {.x = 0, .y = WINDOW_HEIGHT};
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        renderLine(renderer, p3, p1);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        renderLine(renderer, p4, p2);

        SDL_RenderPresent(renderer);

        while(SDL_PollEvent(&event)){
            if (event.type == SDL_EVENT_QUIT){
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                running = false;
            }
        }
    }
    return 0;
}

void renderLine_low(SDL_Renderer* renderer, vec2f p1, vec2f p2){
    f32 dx = p2.x - p1.x;
    f32 dy = p2.y - p1.y;

    f32 yi = 1;
    if (dy < 0){
        yi = -1;
        dy = -dy;
    }
    
    f32 D = (2*dy)-dx;
    f32 y = p1.y;

    for (f32 x = p1.x; x < p2.x; x++){
        SDL_RenderPoint(renderer, x, y);
        if ( D > 0 ){
            y += yi;
            D += 2*(dy - dx);
        }else{
            D += 2*dy;
        }
    }
}

void renderLine_high(SDL_Renderer* renderer, vec2f p1, vec2f p2){
    f32 dx = p2.x - p1.x;
    f32 dy = p2.y - p1.y;

    f32 xi = 1;
    if (dy < 0){
        xi = -1;
        dx = -dx;
    }
    
    f32 D = (2*dx)-dy;
    f32 x = p1.x;

    for (f32 y = p1.y; y < p2.x; y++){
        SDL_RenderPoint(renderer, x, y);
        if ( D > 0 ){
            x += xi;
            D += 2*(dx - dy);
        }else{
            D += 2*dx;
        }
    }
}

void renderLine(SDL_Renderer* renderer, vec2f p1, vec2f p2){
    if ( fabsf(p2.y - p1.y) < fabsf(p2.x - p1.x)){
        if ( p1.x > p2.x) renderLine_low(renderer, p2, p1);
        else renderLine_low(renderer, p1, p2);
    }else {
        if (p1.y > p2.y) renderLine_high(renderer, p2, p1);
        else renderLine_high(renderer, p1, p2);
    }
}
