#include <stdio.h>
#include <stdlib.h>

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

#define windowWidth 640
#define windowHeight 480

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool running = true;

// gamedata
#define mapWidth 24
#define mapHeight 24

u32 worldMap[mapWidth][mapHeight] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
};

void render(){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_FRect wall_block;
    wall_block.y = 0;
    wall_block.w = (f32) (640/24);
    for (u32 i = 0; i < mapWidth; i++){
        for (u32 j = 0; j < mapHeight; j++){
            if (worldMap[i][j] == 2){
                wall_block.x = (f32) (640/24)*j;
                wall_block.h = (f32) (480/24)*i;;
                SDL_SetRenderDrawColor(renderer, 10*i, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(renderer, &wall_block);
                SDL_RenderRect(renderer, &wall_block);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

SDL_Event input_handler(SDL_Event event){
    while(SDL_PollEvent(&event)){
        if (event.type == SDL_EVENT_QUIT){
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            running = false;
        }
    }
    return event;
}

int main(void){
    SDL_CreateWindowAndRenderer("renderer3d", windowWidth, windowHeight, SDL_WINDOW_MOUSE_FOCUS, &window, &renderer);
    if (window == NULL || renderer == NULL){
        SDL_Log("Could not create window || renderer: %s", SDL_GetError());
        running = false;
    }
    SDL_Event event;
    while(running){
        input_handler(event);
        render();
    }
    return 0;
}
