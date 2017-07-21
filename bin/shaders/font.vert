#version 330

in vec4 position;

uniform mat4 transform;

out vec2 uv;

void main() {
    gl_Position = transform * vec4(position.xy, 0, 1);
    uv = position.zw;
}

