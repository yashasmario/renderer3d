#include <SDL3/SDL.h>

#include "../include/base.h"

#include "../include/lines.h"
#include "../include/triangle.h"
#include "../include/matrix.h"

#define windowWidth 640
#define windowHeight 480

bool running  = true;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void input_handler(void){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if (event.type == SDL_EVENT_QUIT){
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            running = false;
        }
    }
}

int main(void){
    SDL_CreateWindowAndRenderer("color_wheel", windowWidth, windowHeight, SDL_WINDOW_MOUSE_FOCUS, &window, &renderer);
    if (window == NULL || renderer == NULL){
        SDL_Log("Could not create window || renderer: %s", SDL_GetError());
        return 1;
    }

    while(running){
        input_handler();
    }
    return 0;
}
