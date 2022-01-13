#version 450

layout(vertices = 3) out;

void main() {
    float nb_frag = 10;
    gl_TessLevelOuter[0] = nb_frag;
    gl_TessLevelOuter[1] = nb_frag;
    gl_TessLevelOuter[2] = nb_frag;

    gl_TessLevelInner[0] = nb_frag;

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
