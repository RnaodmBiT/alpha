#pragma once

#include <string>
#include <SDL.h>
#include <GL/glew.h>

#include <event.hpp>

/*
 * The Application class will encapsulate a window,
 * an application level event queue, and all of the
 * subsystems the game will use.
 */

class Application {
public:
    struct Options {
        std::string title;
        int width, height;
        float updateRate;
    };

    virtual bool Initialize(Options opts);
    virtual void Shutdown();

    void Run();

    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;

    EventQueue Events;

private:

    bool running;
    float timeStep;

    SDL_Window* window;
    SDL_GLContext context;
};

