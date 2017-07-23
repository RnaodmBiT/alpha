#include "font.hpp"
#include "font_5x7.hpp"
#include <cmath>
#include <maths.hpp>
#include <cache.hpp>

void Font::Initialize(const std::string& shaderKey) {

    // Setup the buffers for rendering
    vertexBuffer.Initialize();
    object.Initialize();

    object.BindBuffer(vertexBuffer, 4, GL_FLOAT, false);

    // Load the shader files
    shader = Cache.Get<Shader>(shaderKey);

    // Generate the font atlas from the raw font data
    GenerateFontAtlas();
}


void Font::Shutdown() {
}


void Font::Draw(const vec2& pos, const std::string& text, const vec4& color, int size) {

    static const vec2 quad[] = {
        { 0, 0 }, { 1, 0 }, { 0, 1 },
        { 1, 0 }, { 1, 1 }, { 0, 1}
    };

    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);

    mat4 projection = orthographic(0, 0, (float)vp[2], (float)vp[3]) * translate(pos.x, pos.y, 0.0f) * scale((float)size, (float)size, 0.0f);

    shader->Apply();
    shader->Get("transform") = projection;
    shader->Get("font") = font;
    shader->Get("color") = color;

    float cursorX = 0, cursorY = 0;

    std::vector<vec4> verts;

    for (char c : text) {
        const Glyph& glyph = glyphs[c];

        if (c == '\n') {
            cursorX = 0;
            cursorY += (float)(metrics.height + metrics.lineSpacing);
        } else {

            vec2 glyphUV = glyphs[c].UV(atlasSize);

            for (int i = 0; i < 6; ++i) {
                vec2 pos = { cursorX + (float)metrics.width * quad[i].x,
                             cursorY + (float)metrics.height * quad[i].y };

                vec2 uv = { glyphUV.x + (float)metrics.width / (float)atlasSize * quad[i].x,
                            glyphUV.y + (float)metrics.height / (float)atlasSize * quad[i].y };

                verts.push_back({ pos.x, pos.y, uv.x, uv.y });
            }

            cursorX += (float)metrics.width + 1;
        }
    }

    vertexBuffer.SetData(verts);

    object.Draw((int)verts.size());
}


void Font::Measure(const std::string& text, int size, int& width, int& height) {

    int cursorX = 0, cursorY = 0;
    width = height = 0;

    for (char c : text) {
        if (c == '\n') {
            cursorX = 0;
            cursorY += metrics.height + metrics.lineSpacing;
        } else {
            width = std::max(width, cursorX + metrics.width + 1);
            height = std::max(height, cursorY + metrics.height);

            cursorX += metrics.width + 1;
        }
    }

    width *= size;
    height *= size;
}


void Font::GenerateFontAtlas() {
    const int size = 128;
    atlasSize = size;

    metrics.width = 5;
    metrics.height = 7;
    metrics.lineSpacing = 2;

    RGBA image[size * size];

    int x = 1, y = 1;

    int start = 32;
    int end = 127;

    for (int c = start; c <= end; ++c) {
        for (int i = 0; i < metrics.width; ++i) {
            for (int j = 0; j < metrics.height; ++j) {
                if (Font5x7[(c - start) * metrics.width + i] & (1 << j)) {
                    image[(x + i) + (y + j) * size] = RGBA(255, 255, 255, 255);
                }
            }
        }

        glyphs[c] = { x, y };

        x += metrics.width + 1;
        if (x > size - metrics.width - 1) {
            x = 1;
            y += metrics.height + 1;
        }
    }

    font.SetData(size, size, image);
    font.DisableMipmap();
}

