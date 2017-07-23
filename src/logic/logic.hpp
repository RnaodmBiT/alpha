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

    ActorFactory actorFactory;
    std::map<ActorID, std::unique_ptr<Actor>> actors;

};


class ActorCreatedEvent : public IEvent {
public:
    static EventID GetID() {
        return 0x7A1A1AE4;
    }

    ActorCreatedEvent(ActorID id) : ID(id) { }

    ActorID ID;
};

