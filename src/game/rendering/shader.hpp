#pragma once
#include <GL/glew.h>
#include <map>
#include <string>

class Uniform {
public:
    template <typename T>
    void Set(const T& value);

    template <typename T>
    void operator=(const T& value) {
        Set(value);
    }

private:
    GLuint id;

    friend class Shader;
};


class Shader {
public:

    bool LoadFromFiles(const std::string& vertexFile, const std::string& fragmentFile);

    Uniform& Get(const std::string& name);
    Uniform& operator[](const std::string& name);

    void Apply();

private:

    GLuint BuildShaderSection(GLenum type, const std::string& source);
    bool BuildShader(const std::string& vertexSource, const std::string& fragmentSource);

    GLuint program;
    std::map<std::string, Uniform> uniforms;

};

