#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void renderRect(SDL_Renderer* rernderer, vec2f p1, vec2f p2, vec2f p3, vec2f p4);
void renderFillRect();

int main(void){
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_CreateWindowAndRenderer("WALLS", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    if (window == NULL || renderer == NULL){
        SDL_Log("Failed to create window or renderer : %s", SDL_GetError());
    }
    
    SDL_Event event;
    
    while(running){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

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

void renderRect(SDL_Renderer* renderer, vec2f p1, vec2f p2, vec2f p3, vec2f p4){
    
}
