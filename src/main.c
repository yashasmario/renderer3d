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

#define windowWidth 640
#define windowHeight 480

f32 camera_angle_x = 0;
f32 camera_angle_y = 0;
f32 camera_angle_z = 0;

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

void project(vec3f point, f32 fov, f32* px, f32* py){
    // bypass division by zero bugs and push it away from cam
    f32 z = point.z + 5.0f;
    *px = ((point.x/z) * fov + windowWidth / 2);
    *py = ((point.y/z) * fov + windowHeight/ 2);
}

vec3f rotate_x(vec3f point, f32 a){
    f32 x = point.x;
    f32 y = point.y;
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

void renderCube(){
    Cube cube = {
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

    f32 fov = 300;
    f32 camera_drift = 0.0002;
    camera_angle_y -= camera_drift;
    for (i32 i = 0; i < 12; i++){
        vec3f p1 = cube.vertices[cube.edges[i][0]];
        vec3f p2 = cube.vertices[cube.edges[i][1]];
        
        vec3f rp1 = rotate_y(p1, camera_angle_y);
        rp1 = rotate_x(rp1, camera_angle_x);
        rp1 = rotate_z(rp1, camera_angle_z);
        vec3f rp2 = rotate_y(p2, camera_angle_y);
        rp2 = rotate_x(rp2, camera_angle_x);
        rp2 = rotate_z(rp2, camera_angle_z);

        f32 px1, py1, px2, py2;

        project(rp1, fov, &px1, &py1);
        project(rp2, fov, &px2, &py2);
    
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderLine(renderer, px1, py1, px2, py2);
    }
    SDL_RenderPresent(renderer);
}

void renderPyramid(){
    Pyramid pyramid = {
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

    f32 fov = 300;
    f32 camera_drift = 0.0005;
    camera_angle_y -= camera_drift;
    for (i32 i = 0; i < 8; i++){
        vec3f p1 = pyramid.vertices[pyramid.edges[i][0]];
        vec3f p2 = pyramid.vertices[pyramid.edges[i][1]];
        
        vec3f rp1 = rotate_y(p1, camera_angle_y);
        rp1 = rotate_x(rp1, camera_angle_x);
        rp1 = rotate_z(rp1, camera_angle_z);
        vec3f rp2 = rotate_y(p2, camera_angle_y);
        rp2 = rotate_x(rp2, camera_angle_x);
        rp2 = rotate_z(rp2, camera_angle_z);

        f32 px1, py1, px2, py2;

        project(rp1, fov, &px1, &py1);
        project(rp2, fov, &px2, &py2);
    
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderLine(renderer, px1, py1, px2, py2);
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
        if (event.type == SDL_EVENT_MOUSE_MOTION){
            if (event.motion.state & SDL_BUTTON_LEFT){
                camera_angle_y -= event.motion.xrel / 100;
                camera_angle_x += event.motion.yrel / 100;
            }
            // add momentum 
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
        renderCube();
        // renderPyramid();
    }
    return 0;
}

