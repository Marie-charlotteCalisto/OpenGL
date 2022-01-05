#version 450

layout(location = 1) in vec3 positon;

void main()
{
    gl_Position = vec4(position, 1.0);
}
