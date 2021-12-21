#include "init.hh"

#define TEST_OPENGL_ERROR()                                                             \
    do {		  							\
        GLenum err = glGetError(); 					                        \
        if (err != GL_NO_ERROR) std::cerr << "OpenGL ERROR! " << __LINE__ << std::endl;      \
    } while(0)

GLuint vao_id;
GLuint program_id;

void window_resize(int width, int height)
{
    glViewport(0,0,width, height);
    TEST_OPENGL_ERROR();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    TEST_OPENGL_ERROR();

    glBindVertexArray(vao_id);
    TEST_OPENGL_ERROR();

    glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_data.size());
    TEST_OPENGL_ERROR();

    glBindVertexArray(0);
    TEST_OPENGL_ERROR();

    glutSwapBuffers();
}

void init_glut(int &argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitContextVersion(4,5);
    glutInitContextProfile(GLUT_CORE_PROFILE | GLUT_DEBUG);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1024, 1024);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Shader Programming");
    glutDisplayFunc(display);
    glutReshapeFunc(window_resize);
}

