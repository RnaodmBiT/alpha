#pragma once
#include <GL/glew.h>
#include <string>
#include <cache.hpp>
#include <file.hpp>

struct RGBA {
    uint8_t r, g, b, a;
    RGBA(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 0) : r(r), g(g), b(b), a(a) { }
};

class Texture : public IResource {
public:
    static Texture* LoadResource(const std::string& filename);

    Texture() : texture(0) { }

    ~Texture() {
        Destroy();
    }

    void Destroy() {
        if (texture > 0) {
            glDeleteTextures(1, &texture);
            texture = 0;
        }
    }

    template <typename T>
    void SetData(int width, int height, T* data) {
        if (texture == 0) {
            glGenTextures(1, &texture);
        }

        Bind();

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }

    void Bind() const {
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    void DisableMipmap() {
        Bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    void FromFile(const std::string& filename);

private:
    GLuint texture;
};


class CubeMap : public IResource {
public:
    static CubeMap* LoadResource(const std::string& filename);

    CubeMap() : texture(0) { }

    ~CubeMap() {
        Destroy();
    }

    void Destroy() {
        if (texture > 0) {
            glDeleteTextures(1, &texture);
        }
    }

    void Bind() const {
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    }

    void FromFiles(const std::string& left, const std::string& right, const std::string& top, const std::string& bottom, const std::string& front, const std::string& back);

private:
    template <typename T>
    void SetData(GLenum side, int width, int height, T* data) {
        if (texture == 0) {
            glGenTextures(1, &texture);
        }

        Bind();
        glTexImage2D(side, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }

    GLuint texture;
};

