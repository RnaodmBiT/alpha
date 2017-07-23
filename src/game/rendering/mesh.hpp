#pragma once
#include "buffer.hpp"
#include <string>
#include <vector>
#include <maths.hpp>
#include "shader.hpp"

class Mesh {
public:

    void LoadFromFile(const std::string& filename);

    void SetShader(Shader* shader);

    void Draw(const mat4& projection, const mat4& view, const mat4& world) const;

private:

    Shader* shader;

    struct Part {
        Array object;
        Buffer vertexBuffer, normalBuffer;
        int vertexCount;

        vec4 diffuse;
    };

    std::vector<Part> parts;
};

