#pragma once

#include <string>
#include <SDL.h>
#include <GL/glew.h>

/*
 * The Application class will encapsulate a window,
 * an application level event queue, and all of the
 * subsystems the game will use.
 */

class Application {
public:
    struct options {
        std::string title;
        int width, height;
    };

    virtual bool Initialize(options opts);
    virtual void Shutdown();

    void Run();

    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;

private:

    bool running;

    SDL_Window* window;
    SDL_GLContext context;
};
