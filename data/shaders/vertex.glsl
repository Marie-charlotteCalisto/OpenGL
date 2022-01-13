#version 450

in vec3 position;
in vec3 normalSmooth;

void main() {

  gl_Position = vec4(position, 1.0);

}
