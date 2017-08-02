#pragma once
#include "../actor.hpp"


class SceneObjectComponent : public IComponent {
public:
    static SceneObjectComponent* Create(const json::JSON& node) {
        return new SceneObjectComponent(node.at("mesh").to_string(), node.at("shader").to_string());
    }

    SceneObjectComponent(const std::string& mesh, const std::string& shader) : Mesh(mesh), Shader(shader) { }

    std::string Mesh, Shader;
};

