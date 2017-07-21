#include "logic.hpp"
#include <cstdio>
#include <file.hpp>
#include "actor.hpp"
#include <application.hpp>

class TestComponent : public IComponent {
public:
    TestComponent(float value) : value(value) { }

    float GetValue() const {
        return value;
    }

    static TestComponent* Create(const json& node) {
        return new TestComponent((float)node["value"]);
    }

private:
    float value;
};


bool GameLogic::Initialize(Application* app) {
    events = &app->Events;

    actorFactory.AddCreator("test", TestComponent::Create);

    CreateActor(json::parse(file::read("data/actors/test.json")));

    for (auto& idPtr : actors) {
        Actor* actor = idPtr.second.get();
        TestComponent* test = actor->GetComponent<TestComponent>();
        if (test) {
            printf("Test = %f\n", test->GetValue());
        }
    }

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

