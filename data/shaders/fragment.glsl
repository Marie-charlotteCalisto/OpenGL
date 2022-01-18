#version 450

layout(location=0) out vec4 output_color;

uniform vec3 object_color;

void main() {
  output_color = vec4(object_color, 1.0);
}
