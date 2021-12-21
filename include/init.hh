#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "bunny.hh"

#define TEST_OPENGL_ERROR()                                                             \
    do {		  							\
        GLenum err = glGetError(); 					                        \
        if (err != GL_NO_ERROR) std::cerr << "OpenGL ERROR! line:" << __LINE__ << std::endl;      \
    } while(0)


static GLuint bunny_vao_id;
static GLuint program_id;



void init_glut(int &argc, char *argv[]);

bool init_glew();

void init_GL();

bool init_shaders();

void init_object_vbo();
