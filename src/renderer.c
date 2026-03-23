#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../include/base.h"
#include "../include/matrix.h"
#include "../include/triangle.h"
#include <SDL3/SDL.h>

#define windowWidth 640
#define windowHeight 480

f32 camera_yaw = 0;
f32 camera_pitch = 0;
const f32 FOV = 300;

typedef enum{
    MODEL_CUBE,
    MODEL_PYRAMID,
} ModelType;

typedef struct{
    vec3f vertices[8];
    u32 edges[12][2];
    u32 faces[6][4];
}Cube;

typedef struct {
    vec3f vertices[5];
    u32 edges[8][2];
}Pyramid;

typedef struct {
    vec2f v1, v2, v3;   
}Tri2f;

vec2f project(vec3f point){
    // bypass division by zero bugs and push it away from camera
    f32 z = point.z + 5.0f;
    vec2f p = {
        ((point.x/z) * FOV + windowWidth / 2),
        ((point.y/z) * FOV + windowHeight/ 2),
    };
    return p;
}

vec3f rotate_x(vec3f point, f32 a){
    f32 x = point.x;
    f32 y = point.y;
    f32 z = point.z;
    return (vec3f){ x*cosf(a) + z*sinf(a), y, z*cosf(a) - x*sinf(a) };
}

vec3f rotate_y(vec3f point, f32 a){
    f32 x = point.x; f32 y = point.y;
    f32 z = point.z;
    return (vec3f) { x, y*cosf(a) - z*sinf(a), y*sinf(a) + z*cosf(a) };
}

vec3f rotate_z(vec3f point, f32 a){
    f32 x = point.x;
    f32 y = point.y;
    f32 z = point.z;
    return (vec3f) { x*cosf(a) - y*sinf(a), y*cosf(a) + x*sinf(a), z};
}

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool running = true;

void applyTransform(vec3f *p){
    *p = rotate_x(*p, camera_yaw);
    *p = rotate_y(*p, camera_pitch);
}

void renderCube(f32 dt){
    static const Cube cube = {
        .vertices = {
            {-1, -1, -1}, { 1, -1, -1}, { 1,  1, -1}, {-1,  1, -1},
            {-1, -1,  1}, { 1, -1,  1}, { 1,  1,  1}, {-1,  1,  1},
        },
        .edges = {
            {0,1},{1,2},{2,3},{3,0},
            {4,5},{5,6},{6,7},{7,4},
            {0,4},{1,5},{2,6},{3,7},
        },
        .faces = {
            {0, 1, 2, 3},
            {0, 4, 5, 1}, {1, 5, 6, 2}, {2, 6, 7, 3}, {3, 7, 4, 0},
            {4, 5, 6, 7}
        }
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    f32 rot_speed = 0.1f;
    camera_yaw -= rot_speed * dt;

    // render edges
    for (i32 i = 0; i < 12; i++){
        vec3f p1 = cube.vertices[cube.edges[i][0]];
        vec3f p2 = cube.vertices[cube.edges[i][1]];
        
        applyTransform(&p1);
        applyTransform(&p2);

        vec2f tp1 = project(p1);
        vec2f tp2 = project(p2);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderLine(renderer, tp1.x, tp1.y, tp2.x, tp2.y);
    }
    // render faces
    
    for (int i = 0; i < 6; i++){
        vec3f v1 = cube.vertices[cube.faces[i][0]];
        vec3f v2 = cube.vertices[cube.faces[i][1]];
        vec3f v3 = cube.vertices[cube.faces[i][2]];
        vec3f v4 = cube.vertices[cube.faces[i][3]];

        applyTransform(&v1);
        applyTransform(&v2);
        applyTransform(&v3);
        applyTransform(&v4);

        FTriangle tri1 = {
            .v1 = project(v1),
            .v2 = project(v2),
            .v3 = project(v3),
        };


        FTriangle tri2 = {
            .v1 = project(v1),
            .v2 = project(v4),
            .v3 = project(v3),
        };

        SDL_SetRenderDrawColor(renderer, 120, 120, 120, SDL_ALPHA_OPAQUE);
        renderFillTriangle(renderer, &tri1);
        SDL_SetRenderDrawColor(renderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
        renderFillTriangle(renderer, &tri2);
    }

    SDL_RenderPresent(renderer);
}

void input_handler(void){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if (event.type == SDL_EVENT_QUIT){
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            running = false;
        }
        if (event.type == SDL_EVENT_MOUSE_MOTION){
            if (event.motion.state & SDL_BUTTON_LEFT){
                camera_yaw -= event.motion.xrel / 100.0f;
                camera_pitch += event.motion.yrel / 100.0f;

                if (camera_pitch > M_PI/2) camera_pitch = M_PI/2;
                if (camera_pitch < -M_PI/2) camera_pitch = -M_PI/2;
            }
            // add momentum 
        }
    }
}

int main(void){
    SDL_CreateWindowAndRenderer("renderer3d", windowWidth, windowHeight, SDL_WINDOW_MOUSE_FOCUS, &window, &renderer);
    if (window == NULL || renderer == NULL){
        SDL_Log("Could not create window || renderer: %s", SDL_GetError());
        return 1;
    }

    u64 last_time = SDL_GetTicks();
    while(running){

        u64 now = SDL_GetTicks();
        f32 dt = (now - last_time) / 1000.0f;
        if (dt > 0.1f) dt = 0.1f;

        last_time = now;
        input_handler();
        renderCube(dt);
    }
    return 0;
}

