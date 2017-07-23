#version 330

in vec3 in_position;
in vec3 in_normal;

uniform mat4 projection, view, world;

out vec3 normal;

void main() {
    gl_Position = projection * view * world * vec4(in_position, 1);
    normal = (world * vec4(in_normal, 0)).xyz;
}

