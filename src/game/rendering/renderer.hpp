#pragma once

#include <application.hpp>
#include "font.hpp"

class Renderer {
public:

    void Initialize(Application* app);

    void Shutdown();

    void RenderScene();

private:

    Font font;

};


