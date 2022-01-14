#pragma once

#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "ogl.hh"

/*
enum class SHADER{

    VERTEX= 0,
    TESS_CONTROL,
    TESS_EVALUTATION,
    GEOMETRY,
    COMPUTE,
    FRAGMENT
}
*/

class Program {
public:
    Program() = default;
    ~Program() {if (log) free(log);}

    static Program *make_program(std::vector<std::pair<GLenum, std::string>> shader_paths);

    int getID() {return id;}
    char *get_log();
    bool is_ready();
    void use();
    void setUniform1f(const char *name, float a);
    void setUniform3f(const char *name, float a, float b, float c);
    void setUniformMatrix4fv(const char *name, GLsizei count,
                                      GLboolean transpose,
                                      const GLfloat *value);
    bool is_triangles() {return is_triangle; };

private:

    void set_is_triangles(bool is_triangle_) { is_triangle = is_triangle_; };
    bool is_triangle = true;
    char *log = nullptr;
    int id;
};
