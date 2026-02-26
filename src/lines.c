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


        vec2f p1 = {.x = 124, .y = 0};
        vec2f p2 = {.x = 340, .y = 480};
        vec2f p3 = {.x = 10, .y = 400};
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        renderLine(renderer, p1, p3);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        renderLine(renderer, p1, p2);

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

void renderLine(SDL_Renderer* renderer, vec2f p1, vec2f p2){
    f32 dy = abs(p2.y - p1.y);   
    f32 dx = abs(p2.x - p1.x);   
    f32 D = (f32) 2*(dy-dx);
    
    f32 y = p1.y;
    for (f32 x = p1.x; x < p2.x; x++){

        SDL_RenderPoint(renderer, x, y);

        if (D > 0){
            y++;
            D += (f32) 2*(dy-dx);
        }else {
            D += (f32) 2*dy;
        }
    }
}
