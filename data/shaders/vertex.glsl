#version 450

layout (location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 vs_normal;

uniform mat4 MVP;
void main() {

  gl_Position = vec4(position, 1.0);

  vs_normal = normal;

}
