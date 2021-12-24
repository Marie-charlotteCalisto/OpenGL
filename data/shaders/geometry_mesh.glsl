#version 450
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in vec3 gs_normal[];
in vec3 vertex_color[];
out vec3 color;

const float MAGNITUDE = 1.0;
vec3 object_color = vec3(0.0, 1.0, 1.0);
vec3 light_position = vec3(-10.0, -10.0, -50.0);


uniform mat4 MVP;

void GenerateLine(int begin, int end)
{
    gl_Position = gl_in[begin].gl_Position;
    EmitVertex();
    gl_Position = gl_in[end].gl_Position;
    EmitVertex();
    EndPrimitive();
}

void main()
{
    color = object_color;
    GenerateLine(0, 1); // first vertex normal
    GenerateLine(1, 2); // second vertex normal
    GenerateLine(2, 0); // third vertex normal
}
