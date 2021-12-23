#version 450 core

in float lightFactor;
in vec3 normal;
in vec2 uvCoord;
out vec4 color;

uniform sampler2D _texture;

void main() {
    //color = vec4(1, 0, 0, 1) * lightFactor;
    color = texture(_texture, uvCoord) * lightFactor;
}
