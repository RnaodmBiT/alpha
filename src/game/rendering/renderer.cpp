#include "renderer.hpp"

void Renderer::Initialize(Application* app, SceneCamera* camera) {
    glClearColor(0, 0, 0, 1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    font.Initialize("shaders/font.vert", "shaders/font.frag");

    shader = new Shader;
    shader->LoadFromFiles("shaders/object.vert", "shaders/object.frag");

    transforms.push(mat4());

    scene.Initialize(camera);
}


void Renderer::Shutdown() {

}


void Renderer::DrawScene() {
    scene.Draw(this);
}


void Renderer::DrawText(const vec2& pos, const std::string& text, const vec4& color, int size) {
    font.Draw(pos, text, color, size);
}


vec2 Renderer::MeasureText(const std::string& text, int size) {
    int w, h;
    font.Measure(text, size, w, h);
    return { (float)w, (float)h };
}


void Renderer::SetProjection(const mat4& p) {
    projection = p;
}


void Renderer::SetView(const mat4& v) {
    view = v;
}


void Renderer::PushTransform(const mat4& transform) {
    transforms.push(transforms.top() * transform);
}


void Renderer::PopTransform() {
    transforms.pop();
}


void Renderer::DrawMesh(const Mesh* mesh) {
    shader->Apply();
    shader->Get("projection") = projection;
    shader->Get("view") = view;
    shader->Get("world") = transforms.top();

    mesh->Draw();
}


