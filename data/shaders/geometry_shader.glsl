#version 450

layout(triangles) in;
layout(points, max_vertices=1) out;

in vec3 gs_normal[3];
out vec3 color;

uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;
uniform vec3 object_color;
uniform vec3 light_position;

void main() {
    vec4 origin = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0;
    vec3 normal_iner = (gs_normal[0] + gs_normal[1] + gs_normal[2]) / 3.0;

    vec3 light_dir = normalize(light_position - origin.xyz);

    color = object_color*dot(light_dir, normal_iner);
    gl_Position = projection_matrix * model_view_matrix * origin;
    EmitVertex();

    EndPrimitive();
}
