#pragma once

#include <application.hpp>
#include <stack>
#include <maths.hpp>
#include "font.hpp"
#include "scene.hpp"
#include "mesh.hpp"

class Renderer {
public:

    static void RegisterScripting(Scripting& scripting);

    void Initialize(Application* app, SceneCamera* camera, const std::string& fontShaderKey);

    void Shutdown();

    void DrawScene();

    void DrawText(const vec2& pos, const std::string& text, const vec4& color, int size);
    vec2 MeasureText(const std::string& text, int size);


    // Rendering operations
    void SetProjection(const mat4& projection);
    void SetView(const mat4& view);
    void PushTransform(const mat4& transform);
    void PopTransform();

    void DrawMesh(const Mesh* mesh, const Shader* shader);

private:

    void HandleResizeEvent(ResizeEvent* event);

    Font font;

    Scene scene;

    std::stack<mat4> transforms;
    mat4 projection;
    mat4 view;

};


