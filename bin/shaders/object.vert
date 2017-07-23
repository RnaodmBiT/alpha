#version 330

in vec3 position;

uniform mat4 projection, view, world;

void main() {
    gl_Position = projection * view * world * vec4(position, 1);
}

