#version 450
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

out vec4 object_color;

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
    object_color = vec4(0.2, 0.4, 0.05, 1.0);
    GenerateLine(0, 1); // first vertex normal
    GenerateLine(1, 2); // second vertex normal
    GenerateLine(2, 0); // third vertex normal
}
