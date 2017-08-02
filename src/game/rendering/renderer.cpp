#include "renderer.hpp"
#include <event.hpp>


void Renderer::RegisterScripting(Scripting& scripting) {
    // Register the scene graph nodes
    scripting.add(chaiscript::user_type<SceneCamera>(), "SceneCamera");
    scripting.add(chaiscript::fun(&SceneCamera::SetPosition), "SetPosition");
    scripting.add(chaiscript::fun(&SceneCamera::SetDirection), "SetDirection");
}


void Renderer::Initialize(Application* app, SceneCamera* camera, const std::string& fontShaderKey) {
    glClearColor(0, 0, 0, 1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    font.Initialize(fontShaderKey);

    transforms.push(mat4());

    scene.Initialize(camera);

    Events.Register<ResizeEvent>(this, &Renderer::HandleResizeEvent);
}


void Renderer::Shutdown() {
    Events.Unregister<ResizeEvent>(this);
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


void Renderer::DrawMesh(const Mesh* mesh, const Shader* shader) {
    mesh->Draw(shader, projection, view, transforms.top());
}


void Renderer::HandleResizeEvent(ResizeEvent* event) {
    glViewport(0, 0, event->Width, event->Height);

    SceneCamera* camera = scene.GetCamera();
    if (camera) {
        camera->SetAspectRatio((float)event->Width / (float)event->Height);
    }
}


