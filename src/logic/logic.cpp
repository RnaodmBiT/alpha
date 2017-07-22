#include "logic.hpp"
#include <cstdio>
#include <file.hpp>
#include "actor.hpp"
#include <application.hpp>


bool GameLogic::Initialize(Application* app) {
    // TODO: Add creators for components here

    return true;
}


void GameLogic::Reset() {
}


void GameLogic::Update(float dt) {
}


void GameLogic::CreateActor(const json& desc) {
    Actor* actor = actorFactory.CreateActor(desc);
    if (actor) {
        actors[actor->GetID()].reset(actor);
    } else {
        printf("Error creating actor!\n");
    }
}

