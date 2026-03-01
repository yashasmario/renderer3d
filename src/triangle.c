#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <SDL3/SDL.h>

#include "../include/base.h"
#include "../include/lines.h"
#include "../include/matrix.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

bool running = true;

typedef struct {
    vec2f v1;
    vec2f v2;
    vec2f v3;
}FTriangle;

void renderTriangle(SDL_Renderer *renderer, FTriangle* tri);
void renderFillTriangle(SDL_Renderer *renderer, FTriangle* tri);

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

        FTriangle triangle = {
            .v1 = {
                .x = 300,
                .y = 100,
            },
            .v2 = {
                .x = 500,
                .y = 300,
            },
            .v3 = {
                .x = 100,
                .y = 300,
            },
        };

        // cornflower blue
        // SDL_SetRenderDrawColor(renderer, 100, 149, 237, SDL_ALPHA_OPAQUE);
        renderFillTriangle(renderer, &triangle);

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

void renderTriangle(SDL_Renderer *renderer, FTriangle* tri){
    renderLine(renderer, tri->v1.x, tri->v1.y, tri->v2.x, tri->v2.y);
    renderLine(renderer, tri->v2.x, tri->v2.y, tri->v3.x, tri->v3.y);
    renderLine(renderer, tri->v3.x, tri->v3.y, tri->v1.x, tri->v1.y);
}

// barycentric coordinates
void renderFillTriangle(SDL_Renderer *renderer, FTriangle* tri){
    
    // blue
    vec2f v1 = tri->v1;
    // red
    vec2f v2 = tri->v2;
    // green
    vec2f v3 = tri->v3;
    
    f32 x_l = fminf(v1.x, fminf(v2.x, v3.x));
    f32 x_h = fmaxf(v1.x, fmaxf(v2.x, v3.x));

    f32 y_l = fminf(v1.y, fminf(v2.y, v3.y));
    f32 y_h = fmaxf(v1.y, fmaxf(v2.y, v3.y));

    for (int x = (int) x_l; x < (int) x_h; x++){
        for (int y = (int) y_l; y < (int) y_h; y++){
            vec2f p = {.x = (f32) x, .y = (f32) y};

            // v1
            f32 u = vec2f_cross (
                        vec2f_sub(p, v1),
                        vec2f_sub(v2, v1)
                    ) / 
                     vec2f_cross(
                        vec2f_sub(v3, v1),
                        vec2f_sub(v2, v1)
                    );
            // v2
            f32 v = vec2f_cross (
                        vec2f_sub(p, v2),
                        vec2f_sub(v3, v2)
                    ) / 
                     vec2f_cross(
                        vec2f_sub(v1, v2),
                        vec2f_sub(v3, v2)
                    );
            // v3
            f32 w = 1 - v - u;

            if ( u >= 0 && v >= 0 && w >= 0){
                SDL_SetRenderDrawColor(renderer, 
                        (u8) (u * 255), 
                        (u8) (v * 255), 
                        (u8) (w * 255), 
                        SDL_ALPHA_OPAQUE
                        );
                SDL_RenderPoint(renderer, x, y);
            }
        }
    }
}
