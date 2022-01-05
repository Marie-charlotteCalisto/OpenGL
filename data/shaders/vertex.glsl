#version 450

in vec3 position;
in vec3 normalSmooth;

out vec3 vertex_color;
out vec3 vertex_normal;

vec3 light_color = vec3(1.0, 1.0, 1.0);
vec3 light_position = vec3(-10.0, -10.0, -50.0);

vec3 object_color = vec3(0.0, 1.0, 1.0);

uniform mat4 MVP;

void main() {

  gl_Position = MVP * vec4(position, 1.0);

  float c = clamp(dot(normalize(position - light_position), normalSmooth), 0.0, 1.0);
  vertex_color = object_color * c;

  mat3 normalMatrix = mat3(transpose(inverse(MVP)));
  vertex_normal = normalize(vec3(vec4(normalMatrix * position, 0.0)));
}
