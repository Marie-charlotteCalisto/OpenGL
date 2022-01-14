#version 450

layout (points) in;
layout (triangle_strip, max_vertices=3) out;

in vec3 tess_normal[];
out vec4 object_color;

in float TesslightFactor[];
out float lightFactor;

float grass_scale = 1.0f;
const vec3 grass_vertices[3] = vec3[3](vec3(0.6f, 0.0f, 0.0f), vec3(-0.6f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
const vec4 grass_color[3] = vec4[3](vec4(0.2, 0.4, 0.05, 1.0),vec4(0.2, 0.4, 0.05, 1.0),vec4(0.2, 0.5, 0.05, 1.0));

float amplitude = 1.0f;
float frequency = 0.25f;
uniform float phase;

uniform mat4 MVP;

float rand(vec3 co)
{
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))* co.z) * 43758.5453);
}

mat4 rotation(float angle, vec3 axis)
{

    //rotation transformation matrix:
    return mat4(
            axis.x*axis.x * (1.0f - cos(angle)) + cos(angle),       // column 1 of row 1
            axis.x*axis.y * (1.0f - cos(angle)) + axis.z * sin(angle), // column 2 of row 1
            axis.x*axis.z * (1.0f - cos(angle)) - axis.y * sin(angle), // column 3 of row 1
            0.0,

            axis.y*axis.x * (1.0f - cos(angle)) - axis.z * sin(angle), // column 1 of row 2
            axis.y*axis.y * (1.0f - cos(angle)) + cos(angle),
            axis.y*axis.z * (1.0f - cos(angle)) + axis.x * sin(angle),
            0.0,

            axis.z*axis.x * (1.0f - cos(angle)) + axis.y * sin(angle), // column 1 of row 3
            axis.z*axis.y * (1.0f - cos(angle)) - axis.x * sin(angle),
            axis.z*axis.z * (1.0f - cos(angle)) + cos(angle),
            0.0,

            0.0, // column 1 of row 4
            0.0,
            0.0,
            1.0);
}

void main()
{
    vec4 root_position = mat4(1.0f) * gl_in[0].gl_Position;

    mat4 offset = mat4(1.0f);
    offset[3] = root_position;

    mat4 scale = mat4(1.0f);
    scale[0][0] = grass_scale * 0.1f;
    scale[1][1] = grass_scale * 1.25f;

    float random = rand(root_position.xyz);
    mat4 rotation_y = rotation(radians(random * 360.0f), vec3(0.0f, 1.0f, 0.0f));
    mat4 rotation_x = rotation(radians(random * 30.0f), vec3(1.0f, 0.0f, 0.0f));

    vec3 normal_component =  tess_normal[0];
    vec3 up = vec3(0.0f, 1.0f, 0.0f);
    mat4 tangent_matrix = rotation(
            acos(dot(up, normal_component)),
            cross(up, normal_component));


    vec3 wind_direction = vec3(-1.0f, 0.0f, 0.0f);
    mat4 wind = rotation(
            radians((amplitude * sin(frequency * length(root_position.xyz) + phase) + amplitude) * 15.0f * (1.0f - abs(dot(wind_direction, normal_component)))),
            cross(normal_component, wind_direction)
            );

    for (int i = 0; i < 3; i++) {
        vec4 position = vec4(grass_vertices[i], 1.0f);

        position = scale * position;
        position = rotation_x * position;
        position = rotation_y * position;
        position = tangent_matrix * position;
        position = wind * position;
        position = offset * position;

        gl_Position = MVP * position;
        lightFactor = TesslightFactor[0];
        object_color = grass_color[i];
        EmitVertex();
    }

    EndPrimitive();
}
