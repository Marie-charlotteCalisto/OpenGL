#version 450 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUVCoord;

uniform mat4 MVP;
uniform vec3 lightPosition;

out float lightFactor;
out vec3 normal;
out vec2 uvCoord;

void main() {
    gl_Position = MVP * vec4(vPosition, 1.0);
    lightFactor = dot(normalize(lightPosition - vPosition), normalize(vNormal));
    normal = vNormal;
    uvCoord = vUVCoord;
}
