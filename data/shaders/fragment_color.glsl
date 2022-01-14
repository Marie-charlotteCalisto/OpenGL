#version 450

layout(location=0) out vec4 output_color;
in vec4 object_color;
in float lightFactor;

void main() {
  output_color = object_color * lightFactor;
}
