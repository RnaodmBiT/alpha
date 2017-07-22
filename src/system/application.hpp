#pragma once

#include <string>
#include <SDL.h>
#include <GL/glew.h>

#include <event.hpp>
#include <logic.hpp>

class Application;

extern EventQueue Events;

/*
 * The IView interface represents one of the interfaces
 * Into the game, be it a human, an AI, the network server.
 */
class IGameView {
public:
    virtual ~IGameView() { }

    virtual void OnAttach(Application* app) = 0;
    virtual void OnDetach(Application* app) = 0;

    virtual void Update(float dt) = 0;
    virtual void Draw() { }
};

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

    bool Initialize(Options opts);
    void Shutdown();

    void Run();

    void Update(float dt);
    void Draw();

    void AttachView(IGameView* view);
    void RemoveView(IGameView* view);


private:

    void DispatchInputEvent(SDL_Event& e);

    bool running;
    float timeStep;

    SDL_Window* window;
    SDL_GLContext context;

    GameLogic logic;
    std::vector<std::unique_ptr<IGameView>> views;
};

// Define any events the Application class can generate

class QuitEvent : public IEvent {
public:
    static EventID GetID() {
        return 0x4BBB42E3;
    }
};

class ResizeEvent : public IEvent {
public:
    static EventID GetID() {
        return 0xB4596CBF;
    }

    ResizeEvent(int w, int h) : Width(w), Height(h) { }

    int Width, Height;
};

class KeyboardEvent : public IEvent {
public:
    static EventID GetID() {
        return 0xF0E65F6C;
    }

    KeyboardEvent(bool p, SDL_Keycode key) : Pressed(p), Key(key) { }

    bool Pressed;
    SDL_Keycode Key;
};

class MouseEvent : public IEvent {
public:
    enum Action {
        Pressed,
        Released,
        Moved
    };

    static EventID GetID() {
        return 0xA3C1650B;
    }

    MouseEvent(Action t, int b, int x, int y) : Type(t), Button(b), X(x), Y(y) { }

    Action Type;
    int Button;
    int X, Y;
};
