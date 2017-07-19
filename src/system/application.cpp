#include "application.hpp"

#include <cstdio>

bool Application::Initialize(options opts) {
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create a window for the game
    window = SDL_CreateWindow(opts.title.c_str(),
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              opts.width,
                              opts.height,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        printf("Error creating SDL window.\n");
        return false;
    }

    // Initialize OpenGL
    context = SDL_GL_CreateContext(window);
    if (!context) {
        printf("Error creating OpenGL context\n");
        return false;
    }

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        printf("Error initializing GLEW\n");
        return false;
    }

    return true;
}


void Application::Run() {
    running = true;

    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                running = false;
                break;
            }
        }

        // TODO: fix this timestep
        Update(0.0f);
        Draw();

        SDL_GL_SwapWindow(window);
    }
}


void Application::Shutdown() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);

    SDL_Quit();
}
