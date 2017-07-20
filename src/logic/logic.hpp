#pragma once
#include <event.hpp>

class GameLogic {
public:

    bool Initialize();

    void Reset();

    void Update(float dt);

    EventQueue Events;

private:

    // TODO: add a list of actors

};

