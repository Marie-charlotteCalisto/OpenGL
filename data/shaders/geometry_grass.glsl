#version 450

layout (points) in;
layout (triangle_strip, max_vertices=3) out;

void GenerateLine(int pos)
{
    gl_Position = gl_in[pos].gl_Position;
    EmitVertex();
    gl_Position = gl_in[pos].gl_Position + vec4(5.0, 0.0, 0.0, 1.0);
    EmitVertex();
    gl_Position = gl_in[pos].gl_Position + vec4(0.0, 5.0, 0.0, 1.0);
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GenerateLine(0); // first vertex normal
}
