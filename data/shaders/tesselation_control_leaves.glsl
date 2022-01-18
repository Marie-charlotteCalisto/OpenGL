#version 450

layout(vertices = 3) out;

in  vec3 vs_normal [];
patch out vec3 patch_normal;

void main() {
    float nb_frag = 10;
    gl_TessLevelOuter[0] = nb_frag;
    gl_TessLevelOuter[1] = nb_frag;
    gl_TessLevelOuter[2] = nb_frag;

    gl_TessLevelInner[0] = nb_frag;

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    patch_normal = vs_normal[gl_InvocationID];
}
