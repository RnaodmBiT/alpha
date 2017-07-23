#pragma once
#include "buffer.hpp"
#include <string>
#include <maths.hpp>

class Mesh {
public:

    void LoadFromFile(const std::string& filename);

    void Draw() const;

private:

    Array object;
    Buffer vertexBuffer;

    int vertexCount;

};

