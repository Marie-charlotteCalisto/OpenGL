#version 450

layout(triangles, equal_spacing, ccw, point_mode) in;

uniform mat4 MVP;
uniform mat4 model_view;
uniform vec3 lightPosition;


patch in  vec3 patch_normal;
out vec3 tess_normal;
out float TesslightFactor;

float p(float t)
{
    float r = 1;
    return (r - t)*(r - t) * (r + t) * (r + t);
}

float f(float x, float y)
{
    float min = 1;
    float s = sqrt(x*x + y*y);
    if(min > s)
        return p(s);
    return p(min);
}



void main()
{
    vec4 p1 = gl_in[0].gl_Position * gl_TessCoord.x;
    vec4 p2 = gl_in[1].gl_Position * gl_TessCoord.y;
    vec4 p3 = gl_in[2].gl_Position * gl_TessCoord.z;
    vec4 p = p1 + p2 + p3;

    vec4 off = f(p.x*0.05f, p.z*0.05f)*vec4(0.0, 10.0, 0.0, 0.0);;
    gl_Position = p + off;


    vec3 A = gl_in[0].gl_Position.xyz - gl_in[1].gl_Position.xyz;
    vec3 B = gl_in[0].gl_Position.xyz - gl_in[2].gl_Position.xyz;

    tess_normal = patch_normal;

    TesslightFactor = dot(normalize(lightPosition - p.xyz), normalize(tess_normal));
}
