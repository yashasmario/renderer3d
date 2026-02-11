#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glad/glad.h>

#include "iostream"

using namespace std;

int main(int argc, char* argv[]){
    if (!SDL_Init(SDL_INIT_VIDEO)){
        return -1;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // 3. Create Window with OpenGL Support
    SDL_Window* window = SDL_CreateWindow("SDL3 + OpenGL", 800, 600, SDL_WINDOW_OPENGL);
    if (!window) return -1;

    // 4. Create the Context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    
    // 5. Load OpenGL Functions via GLAD
    // SDL_GL_GetProcAddress is the magic link between SDL and GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        cout << "GLAD failed to initialize" << endl;
        return -1;
    }

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }

        // Rendering commands
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the back buffer to the front (display it)
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
