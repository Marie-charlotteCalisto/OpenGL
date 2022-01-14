#version 450

layout (points) in;
layout (triangle_strip, max_vertices=3) out;

in vec3 tess_normal[];
in vec3 color[];
out vec3 object_color;

void GenerateLine(int pos)
{
    gl_Position = gl_in[pos].gl_Position + vec4(tess_normal[0]*10, 1.0);
    EmitVertex();
    gl_Position = gl_in[pos].gl_Position + vec4(-0.5, 0.0, 0.0, 1.0);
    EmitVertex();
    gl_Position = gl_in[pos].gl_Position + vec4(0.5, 0.0, 0.0, 1.0);
    EmitVertex();
    EndPrimitive();
}

void main()
{
    object_color = color[0];
    GenerateLine(0); // first vertex normal
}
