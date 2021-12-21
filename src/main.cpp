#include "init.hh"

int main(int argc, char *argv[])
{
    init_glut(argc, argv);
    if (!init_glew())
        std::exit(-1);
    init_GL();
    init_shaders();
    init_object_vbo();

    glutMainLoop();
}
