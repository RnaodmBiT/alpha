#version 330

uniform vec4 diffuse;
uniform vec3 light = vec3(2, 1, -2);

in vec3 normal;

out vec4 color;


void main() {
    color.xyz = diffuse.xyz * clamp(dot(normalize(normal), normalize(light)), 0, 1);

    color.xyz = pow(color.xyz, vec3(1.0f / 2.2f, 1.0f / 2.2f, 1.0f / 2.2f));
    color.w = 1.0f;
}

