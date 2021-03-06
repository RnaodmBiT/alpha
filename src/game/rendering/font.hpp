#pragma once
#include "shader.hpp"
#include "texture.hpp"
#include "buffer.hpp"
#include <map>
#include <maths.hpp>

class Font {
public:
    void Initialize(const std::string& shaderKey);

    void Shutdown();

    void Draw(const vec2& pos, const std::string& text, const vec4& color = { 1, 1, 1, 1 }, int size = 1);

    void Measure(const std::string& text, int size, int& width, int& height);

private:

    struct Glyph {
        int x, y;

        vec2 UV(int size) const {
            return { (float)x / (float)size, (float)y / (float)size };
        }
    };

    void GenerateFontAtlas();

    const Shader* shader;
    Texture font;
    int atlasSize;

    Buffer vertexBuffer;
    Array object;

    std::map<int, Glyph> glyphs;

    struct {
        int width, height;
        int lineSpacing;
    } metrics;

};
