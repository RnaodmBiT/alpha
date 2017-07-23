#pragma once
#include "buffer.hpp"
#include <string>
#include <vector>
#include <maths.hpp>
#include "shader.hpp"
#include <cache.hpp>

class Mesh : public IResource {
public:

    static Mesh* LoadResource(const std::string& filename);

    void LoadFromFile(const std::string& filename);

    void Draw(const Shader* shader, const mat4& projection, const mat4& view, const mat4& world) const;

private:

    struct Part {
        Array object;
        Buffer vertexBuffer, normalBuffer;
        int vertexCount;

        vec4 diffuse;
    };

    std::vector<Part> parts;
};

