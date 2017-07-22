#pragma once

#include <application.hpp>
#include "font.hpp"

class Renderer {
public:

    void Initialize(Application* app);

    void Shutdown();

    void DrawScene();

    void DrawText(const vec2& pos, const std::string& text, const vec4& color, int size);

private:

    Font font;

};


