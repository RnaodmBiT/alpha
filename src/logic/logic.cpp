#include "logic.hpp"
#include <cstdio>
#include <file.hpp>
#include "actor.hpp"
#include <application.hpp>
#include "components/common.hpp"


bool GameLogic::Initialize(Application* app) {
    // TODO: Add creators for components here
    actorFactory.AddCreator("SceneObject", &SceneObjectComponent::Create);

    Events.Register<RequestCreateActorEvent>(this, &GameLogic::HandleRequestCreateActor);

    return true;
}


void GameLogic::Reset() {
}


void GameLogic::Update(float dt) {
}


void GameLogic::CreateActor(const json::JSON& desc) {
    Actor* actor = actorFactory.CreateActor(desc);
    if (actor) {
        actors[actor->GetID()].reset(actor);
        Events.QueueEvent<ActorCreatedEvent>(new ActorCreatedEvent(actor));
    } else {
        printf("Error creating actor!\n");
    }
}


void GameLogic::HandleRequestCreateActor(RequestCreateActorEvent* event) {
    CreateActor(json::JSON::Load(File::Read("data/actors/" + event->Type + ".json")));
}

