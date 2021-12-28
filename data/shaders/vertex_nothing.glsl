#version 450

layout(location = 1) in vec3 vPositon;

void main()
{
    gl_Position = vec4(vPosition, 1.0);
}
