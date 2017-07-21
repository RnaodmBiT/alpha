#include "renderer.hpp"

void Renderer::Initialize(Application* app) {
    glClearColor(1, 0, 0, 1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    font.Initialize("shaders/font.vert", "shaders/font.frag");
}


void Renderer::Shutdown() {

}


void Renderer::RenderScene() {
    font.Draw(0, 0, "Hello World!\nI like pie!", { 0, 0, 1, 1 });
}

