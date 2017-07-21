#pragma once
#include <event.hpp>
#include "actor.hpp"

class Application;

class GameLogic {
public:

    bool Initialize(Application* app);

    void Reset();

    void Update(float dt);

private:

    void CreateActor(const json& desc);

    EventQueue* events;
    ActorFactory actorFactory;
    std::map<ActorID, std::unique_ptr<Actor>> actors;

};

