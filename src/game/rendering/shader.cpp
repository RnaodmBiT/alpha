#include "shader.hpp"
#include <file.hpp>
#include <maths.hpp>
#include "texture.hpp"

// TODO: Implement Uniform::Set

template <>
void Uniform::Set<mat4>(const mat4& value) {
    glUniformMatrix4fv(id, 1, true, value.data.data());
}

template <>
void Uniform::Set<Texture>(const Texture& value) {
    glUniform1i(id, 0);
    glActiveTexture(GL_TEXTURE0);
    value.Bind();
}

template <>
void Uniform::Set<vec4>(const vec4& value) {
    glUniform4f(id, value.x, value.y, value.z, value.w);
}


bool Shader::LoadFromFiles(const std::string& vertexFile, const std::string& fragmentFile) {
    return BuildShader(file::read(vertexFile), file::read(fragmentFile));
}


Uniform& Shader::Get(const std::string& name) {
    if (!uniforms.count(name)) {
        uniforms[name].id = glGetUniformLocation(program, name.c_str());
    }

    return uniforms[name];
}


Uniform& Shader::operator[](const std::string& name) {
    return Get(name);
}


void Shader::Apply() {
    glUseProgram(program);
}

GLuint Shader::BuildShaderSection(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);

    const char* str = source.c_str();
    int length = source.size();

    glShaderSource(shader, 1, &str, &length);
    glCompileShader(shader);

    int compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled) {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        std::string log(length, ' ');
        glGetShaderInfoLog(shader, length, &length, &log[0]);
        printf("Shader log: %s\n", log.c_str());
        return 0;
    }

    return shader;
}

bool Shader::BuildShader(const std::string& vertexSource, const std::string& fragmentSource) {
    // Build the individual shaders
    GLuint vertex = BuildShaderSection(GL_VERTEX_SHADER, vertexSource);
    GLuint fragment = BuildShaderSection(GL_FRAGMENT_SHADER, fragmentSource);

    if (vertex == 0 || fragment == 0) {
        return false;
    }

    // Create a program and link the shaders to it
    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    int linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    // Check if it linked okay
    if (!linked) {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        std::string log(length, ' ');
        glGetShaderInfoLog(program, length, &length, &log[0]);
        printf("Program log: %s\n", log.c_str());
        return false;
    }

    // Free up the shader resources
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}
