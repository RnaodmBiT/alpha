#include "application.hpp"

#include <cstdio>
#include "time.hpp"

EventQueue Events;

bool Application::Initialize(Options opts) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

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


    // Initialize the logic for the game itself
    if (!logic.Initialize(this)) {
        return false;
    }

    timeStep = 1.0f / opts.updateRate;

    // Setup any events the application needs to respond too
    Events.Register<QuitEvent>(this, [&] (QuitEvent*) { running = false; });

    return true;
}


void Application::Run() {
    running = true;

    float accumulator = 0.0f;
    Stopwatch time;

    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                    Events.TriggerEvent(new ResizeEvent(e.window.data1, e.window.data2));
                }
                break;

            default:
                DispatchInputEvent(e);
                break;
            }
        }

        accumulator += time.Reset();

        while (accumulator > timeStep) {
            Update(timeStep);
            accumulator -= timeStep;
        }

        Draw();
    }
}


void Application::Update(float dt) {
    Events.UpdateQueue();
    logic.Update(dt);

    for (auto& view : views) {
        view->Update(dt);
    }
}


void Application::Draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto& view : views) {
        view->Draw();
    }

    SDL_GL_SwapWindow(window);
}


void Application::Shutdown() {
    printf("Shutdown\n");
    logic.Reset();

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);

    SDL_Quit();
}


void Application::AttachView(IGameView* view) {
    views.emplace_back(view);
    view->OnAttach(this);
}


void Application::RemoveView(IGameView* view) {
    view->OnDetach(this);
    auto it = std::remove_if(views.begin(), views.end(), [view] (const std::unique_ptr<IGameView>& ptr) { return ptr.get() == view; });
    views.erase(it, views.end());
}


void Application::DispatchInputEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        Events.TriggerEvent(new KeyboardEvent(true, e.key.keysym.sym));
    } else if (e.type == SDL_KEYUP) {
        Events.TriggerEvent(new KeyboardEvent(false, e.key.keysym.sym));
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        Events.TriggerEvent(new MouseEvent(MouseEvent::Pressed, e.button.button, e.button.x, e.button.y));
    } else if (e.type == SDL_MOUSEBUTTONUP) {
        Events.TriggerEvent(new MouseEvent(MouseEvent::Released, e.button.button, e.button.x, e.button.y));
    } else if (e.type == SDL_MOUSEMOTION) {
        Events.TriggerEvent(new MouseEvent(MouseEvent::Moved, 0, e.motion.x, e.motion.y));
    }
}

