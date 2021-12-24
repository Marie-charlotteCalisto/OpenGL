#version 450

layout(triangles) in;
layout(points, max_vertices=1) out;

in vec3 gs_normal[3];
out vec3 color;

uniform mat4 MVP;
vec3 object_color = vec3(0.0, 1.0, 1.0);
vec3 light_position = vec3(-10.0, -10.0, -50.0);

void main() {
    vec4 origin = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0;
    vec3 normal_iner = (gs_normal[0] + gs_normal[1] + gs_normal[2]) / 3.0;

    vec3 light_dir = normalize(light_position - origin.xyz);

    color = object_color*dot(light_dir, normal_iner);
    gl_Position = MVP * origin;
    EmitVertex();

    EndPrimitive();
}
