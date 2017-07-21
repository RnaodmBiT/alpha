#include "logic.hpp"
#include <cstdio>
#include <file.hpp>
#include "actor.hpp"

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


bool GameLogic::Initialize() {

    ActorFactory factory;
    factory.AddCreator("test", TestComponent::Create);

    Actor* actor = factory.CreateActor(json::parse(file::read("data/actors/test.json")));

    TestComponent* test = actor->GetComponent<TestComponent>();
    printf("Actor has component with value = %f\n", test->GetValue());

    return true;
}


void GameLogic::Reset() {
}


void GameLogic::Update(float dt) {
}

