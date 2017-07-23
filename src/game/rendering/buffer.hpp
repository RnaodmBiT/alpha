#pragma once
#include <GL/glew.h>
#include <vector>

class Buffer {
public:
    Buffer(GLenum type = GL_ARRAY_BUFFER) : type(type), buffer(0) { }

    ~Buffer() {
        Destroy();
    }

    void Initialize() {
        glGenBuffers(1, &buffer);
    }

    void Destroy() {
        if (buffer > 0) {
            glDeleteBuffers(1, &buffer);
        }
    }

    template <typename T>
    void SetData(int count, const T* data) {
        Bind();
        glBufferData(type, count * sizeof(T), data, GL_DYNAMIC_DRAW);
    }

    template <typename T>
    void SetData(const std::vector<T>& data) {
        SetData((int)data.size(), data.data());
    }

    void Bind() {
        glBindBuffer(type, buffer);
    }

private:

    GLenum type;
    GLuint buffer;
};


class Array {
public:
    Array() : array(0), attributes(0) { }

    ~Array() {
        Destroy();
    }

    void Initialize() {
        glGenVertexArrays(1, &array);
    }

    void Destroy() {
        if (array > 0) {
            glDeleteVertexArrays(1, &array);
        }
    }

    void BindBuffer(Buffer& buffer, int components, GLenum type, bool normalized) {
        Bind();

        glEnableVertexAttribArray(attributes);

        buffer.Bind();
        glVertexAttribPointer(attributes++, components, type, normalized, 0, 0);
    }

    void Bind() const {
        glBindVertexArray(array);
    }

    void Draw(int vertices, GLenum type = GL_TRIANGLES) const {
        Bind();
        glDrawArrays(type, 0, vertices);
    }

private:
    GLuint array;
    int attributes;
};

