#include "renderer.hpp"

void Renderer::Initialize(Application* app) {
    glClearColor(0, 0, 0, 1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    font.Initialize("shaders/font.vert", "shaders/font.frag");
}


void Renderer::Shutdown() {

}


void Renderer::DrawScene() {
    // TODO: Add this once we have a scene graph implemented
}


void Renderer::DrawText(const vec2& pos, const std::string& text, const vec4& color, int size) {
    font.Draw(pos, text, color, size);
}


vec2 Renderer::MeasureText(const std::string& text, int size) {
    int w, h;
    font.Measure(text, size, w, h);
    return { (float)w, (float)h };
}

