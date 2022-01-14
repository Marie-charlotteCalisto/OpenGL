#version 450

layout (points) in;
layout (triangle_strip, max_vertices=3) out;

in vec3 tess_normal[];
in vec3 color[];
out vec3 object_color;

float grass_scale = 10.0f;
const vec3 grass_vertices[3] = vec3[3](vec3(0.5f, 0.0f, 0.0f), vec3(-0.5f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

uniform mat4 MVP;

float rand(vec2 co)
{
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

mat4 rotation(float angle, vec3 axis)
{

    // Specify the rotation transformation matrix:
    mat4 m = mat4(
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

    return m;
}

void main()
{
    vec4 root_position = mat4(1.0f) * gl_in[0].gl_Position;

    mat4 offset = mat4(1.0f);
    offset[3] = root_position;

    mat4 scale = mat4(1.0f);
    scale[0][0] = grass_scale * 0.1f;
    scale[1][1] = grass_scale * 1.25f;

    float random = rand(root_position.xy);
    mat4 rotation_y = rotation(radians(random * 360.0f), vec3(0.0f, 1.0f, 0.0f));
    mat4 rotation_x = rotation(radians(random * 30.0f), vec3(1.0f, 0.0f, 0.0f));

    vec3 normal_component =  tess_normal[0];
    vec3 up = vec3(0.0f, 1.0f, 0.0f);
    mat4 tangent_matrix = rotation(
            acos(dot(up, normal_component)),
            cross(up, normal_component) // already normalized
            );


    for (int i = 0; i < 3; i++) {
        vec4 position = vec4(grass_vertices[i], 1.0f);

        position = scale * position;
        position = rotation_x * position;
        position = rotation_y * position;
        position = tangent_matrix * position;
        position = offset * position;

        gl_Position = MVP * position;
        object_color = color[0];
        EmitVertex();
    }

    EndPrimitive();
}
