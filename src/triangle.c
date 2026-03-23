#include <math.h>
#include <SDL3/SDL.h>

#include "../include/base.h"
#include "../include/lines.h"
#include "../include/matrix.h"

typedef struct {
    vec2f v1;
    vec2f v2;
    vec2f v3;
}FTriangle;

void renderTriangle(SDL_Renderer *renderer, FTriangle* tri);
void renderFillTriangle(SDL_Renderer *renderer, FTriangle* tri);

void renderTriangle(SDL_Renderer *renderer, FTriangle* tri){
    renderLine(renderer, tri->v1.x, tri->v1.y, tri->v2.x, tri->v2.y);
    renderLine(renderer, tri->v2.x, tri->v2.y, tri->v3.x, tri->v3.y);
    renderLine(renderer, tri->v3.x, tri->v3.y, tri->v1.x, tri->v1.y);
}

// barycentric coordinates
void renderFillTriangle(SDL_Renderer *renderer, FTriangle* tri){
    
    vec2f v1 = tri->v1;
    vec2f v2 = tri->v2;
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
                //SDL_SetRenderDrawColor(renderer, 
                        //(u8) (u * 255), 
                        //(u8) (v * 255), 
                        //(u8) (w * 255), 
                        //SDL_ALPHA_OPAQUE
                        //);
                SDL_RenderPoint(renderer, x, y);
            }
        }
    }
}
