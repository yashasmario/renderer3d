#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "../include/base.h"
#include "../include/lines.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

bool running = true;

typedef struct {
    f32 x;
    f32 y; 
    f32 h;
    f32 w;
}RectF;

void renderRect(SDL_Renderer* renderer, RectF* rect);
void renderFillRect(SDL_Renderer* renderer, RectF* rect);

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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        RectF rect;
        rect.h = rect.w = 150;
        rect.x = rect.y = 100;

        renderRect(renderer, &rect);

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

void renderRect(SDL_Renderer* renderer, RectF* rect){
    f32 h = rect->h;
    f32 w = rect->w;
    f32 x = rect->x;
    f32 y = rect->y;
    
    renderLine(renderer, x, y, x+w, y);
    renderLine(renderer, x+w, y, x+w, y+h);
    renderLine(renderer, x+w, y+h, x, y+h);
    renderLine(renderer, x, y+h, x, y);
}

void renderFillRect(SDL_Renderer* renderer, RectF* rect);
