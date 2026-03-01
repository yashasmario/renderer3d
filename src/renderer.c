#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/base.h"
#include <SDL3/SDL.h>

#define windowWidth 640
#define windowHeight 480

f32 camera_yaw = 0;
f32 camera_pitch = 0;
const f32 FOV = 300;

typedef struct {
    f32 x, y, z;
}vec3f;

typedef struct{
    vec3f vertices[8];
    u32 edges[12][2];
}Cube;

typedef struct {
    vec3f vertices[5];
    u32 edges[8][2];
}Pyramid;


vec3f vec_add(vec3f p1, vec3f p2){
    return (vec3f){ p1.x + p2.x, p1.y + p2.y, p1.z + p2.z };
}

vec3f vec_pdt(vec3f p1, vec3f p2){
    return (vec3f) { p1.x*p2.x, p1.y*p2.y, p1.z*p2.z };
}

void project(vec3f point, f32* px, f32* py){
    // bypass division by zero bugs and push it away from cam
    f32 z = point.z + 5.0f;
    *px = ((point.x/z) * FOV + windowWidth / 2);
    *py = ((point.y/z) * FOV + windowHeight/ 2);
}

vec3f rotate_x(vec3f point, f32 a){
    f32 x = point.x; f32 y = point.y;
    f32 z = point.z;
    return (vec3f) { x, y*cosf(a) - z*sinf(a), z*cosf(a) + y*sinf(a) };
}

vec3f rotate_y(vec3f point, f32 a){
    f32 x = point.x;
    f32 y = point.y;
    f32 z = point.z;
    return (vec3f){ x*cosf(a) + z*sinf(a), y, z*cosf(a) - x*sinf(a) };
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
        }
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    f32 rot_speed = 0.1f;
    camera_yaw -= rot_speed * dt;
    for (i32 i = 0; i < 12; i++){
        vec3f p1 = cube.vertices[cube.edges[i][0]];
        vec3f p2 = cube.vertices[cube.edges[i][1]];
        
        vec3f rp1 = rotate_y(p1, camera_yaw);
        rp1 = rotate_x(rp1, camera_pitch);
        vec3f rp2 = rotate_y(p2, camera_yaw);
        rp2 = rotate_x(rp2, camera_pitch);

        f32 px1, py1, px2, py2;

        project(rp1, &px1, &py1);
        project(rp2, &px2, &py2);
    
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderLine(renderer, px1, py1, px2, py2);
    }
    SDL_RenderPresent(renderer);
}

void renderPyramid(f32 dt){
    static const Pyramid pyramid = {
        .vertices = {
            {0, -2, 0}, // height
            {1, 0, 0}, {-1, 0, 0}, {0, 0, 1}, {0, 0, -1} // base
        },
        .edges = {
            {0, 1}, {0, 2}, {0, 3}, {0, 4}, // top
            {1, 3}, {2, 4}, {2, 3}, {1, 4} // base
        }
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    f32 rot_speed = 0.5f;
    camera_yaw -= rot_speed * dt;
    for (i32 i = 0; i < 8; i++){
        vec3f p1 = pyramid.vertices[pyramid.edges[i][0]];
        vec3f p2 = pyramid.vertices[pyramid.edges[i][1]];
        
        vec3f rp1 = rotate_y(p1, camera_yaw);
        rp1 = rotate_x(rp1, camera_pitch);
        vec3f rp2 = rotate_y(p2, camera_yaw);
        rp2 = rotate_x(rp2, camera_pitch);

        f32 px1, py1, px2, py2;

        project(rp1, &px1, &py1);
        project(rp2, &px2, &py2);
    
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderLine(renderer, px1, py1, px2, py2);
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
        // renderPyramid(dt);
    }
    return 0;
}

