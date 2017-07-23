#pragma once

#include <application.hpp>
#include <stack>
#include <maths.hpp>
#include "font.hpp"
#include "scene.hpp"
#include "mesh.hpp"

class Renderer {
public:

    void Initialize(Application* app, SceneCamera* camera);

    void Shutdown();

    void DrawScene();

    void DrawText(const vec2& pos, const std::string& text, const vec4& color, int size);
    vec2 MeasureText(const std::string& text, int size);


    // Rendering operations
    void SetProjection(const mat4& projection);
    void SetView(const mat4& view);
    void PushTransform(const mat4& transform);
    void PopTransform();

    void DrawMesh(const Mesh* mesh);

private:

    Font font;

    Scene scene;

    Shader* shader;

    std::stack<mat4> transforms;
    mat4 projection;
    mat4 view;

};


