#version 450


vec3 object_color = vec3(0.3, 1.0, 0.0);
layout(location=0) out vec4 output_color;

void main() {
  output_color = vec4(object_color, 1.0);
}
