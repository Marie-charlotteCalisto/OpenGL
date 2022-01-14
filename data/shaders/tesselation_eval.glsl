#version 450

layout(triangles, equal_spacing, ccw, point_mode) in;

uniform mat4 MVP;
vec3 light_position = vec3(-10.0, -10.0, -50.0);

out vec3 tess_normal;
out vec3 color;

void main()
{
    vec4 p1 = gl_in[0].gl_Position * gl_TessCoord.x;
    vec4 p2 = gl_in[1].gl_Position * gl_TessCoord.y;
    vec4 p3 = gl_in[2].gl_Position * gl_TessCoord.z;
    vec4 p = p1 + p2 + p3;

    gl_Position = MVP * p;


    vec3 A = gl_in[0].gl_Position.xyz - gl_in[1].gl_Position.xyz;
    vec3 B = gl_in[0].gl_Position.xyz - gl_in[2].gl_Position.xyz;

    tess_normal = normalize(cross(A,B));

    float c = clamp(dot(normalize(vec3(p) - light_position), tess_normal), 0.0, 1.0);
    color = vec3(0.3, 1.0, 0.0) * c;
}
