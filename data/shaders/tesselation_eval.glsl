#version 450

layout (triangles, equal_spacing, ccw, point_mode) in;

uniform mat4 MVP;

void main()
{
    vec4 p1 = gl_in[0].gl_Position * gl_TessCoord.x;
    vec4 p2 = gl_in[1].gl_Position * gl_TessCoord.y;
    vec4 p3 = gl_in[2].gl_Position * gl_TessCoord.z;
    vec4 p = p1 + p2 + p3;

    gl_Position = MVP * p;
}
