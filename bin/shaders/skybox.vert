#version 330

in vec3 in_position;

uniform mat4 projection, view, world;

out vec3 position;

void main() {
    gl_Position = projection * view * world * vec4(in_position, 1);
    position = in_position;
}

