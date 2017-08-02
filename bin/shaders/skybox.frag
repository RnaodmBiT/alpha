#version 330

in vec3 position;

uniform samplerCube cube;

out vec4 color;

void main() {
    color = texture(cube, position);
    // color = vec4(1, 0, 0, 1);
}

