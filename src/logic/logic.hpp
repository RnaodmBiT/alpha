#pragma once
#include <event.hpp>
#include <chaiscript.hpp>
#include "actor.hpp"

class Application;

class RequestCreateActorEvent : public IEvent {
public:
    static EventID GetID() {
        return 0x84F9268C;
    }

    RequestCreateActorEvent(const std::string& type) : Type(type) { }
    std::string Type;
};


class ActorCreatedEvent : public IEvent {
public:
    static EventID GetID() {
        return 0x7A1A1AE4;
    }

    ActorCreatedEvent(Actor* actor) : Object(actor) { }
    Actor* Object;
};


class GameLogic {
public:

    bool Initialize(Application* app);

    void Reset();

    void Update(float dt);

private:

    void CreateActor(const json::JSON& desc);

    void HandleRequestCreateActor(RequestCreateActorEvent* event);

    ActorFactory actorFactory;
    std::map<ActorID, std::unique_ptr<Actor>> actors;

};


