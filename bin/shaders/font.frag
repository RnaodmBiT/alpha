#version 330

in vec2 uv;

uniform sampler2D font;
uniform vec4 color = vec4(1, 1, 1, 1);

out vec4 fragColor;

void main() {
    fragColor = mix(vec4(color.xyz, 0), color, texture(font, uv).x);
}

