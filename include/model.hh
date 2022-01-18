#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "ogl.hh"
#include "mesh.hh"
#include "objloader.hh"
#include "program.hh"

#define TEST_OPENGL_ERROR()                                                             \
    do {                                                                                \
        GLenum err = glGetError();                                                      \
        if (err != GL_NO_ERROR) std::cerr << "OpenGL ERROR!" << __LINE__ << std::endl;  \
    } while(0)


class Model
{
public:
    std::vector<Mesh> meshes;

    // constructor, expects a filepath to a 3D model.
    Model(const char *path,
            std::vector<std::string> texture_path,
            Program *_shader,
            float s, float xoff, float yoff, float zoff)
    {
        loadModel(path, texture_path);
        scale = s;
        xo = xoff;
        yo = yoff;
        zo = zoff;
        shader = _shader;
    }

void Draw(glm::mat4 projection, glm::mat4 view, float nb_frag, float wind_power, GLuint matID);
    // draws the model, and thus all its meshes


private:
    float scale, xo, yo, zo;
    Program *shader;
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(const char *path, std::vector<std::string> texture_path);

};
