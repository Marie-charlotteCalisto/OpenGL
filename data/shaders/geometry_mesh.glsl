#version 450
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

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
    GenerateLine(0, 1); // first vertex normal
    GenerateLine(1, 2); // second vertex normal
    GenerateLine(2, 0); // third vertex normal
}
