#version 450

in vec3 position;
in vec3 normalSmooth;

uniform mat4 MVP;

out vec3 vertex_normal;

void main() {

  gl_Position = vec4(position, 1.0);

  mat4 normalMatrix = transpose(inverse(MVP));
  vertex_normal = normalize(vec3(normalMatrix * gl_Position));
}
