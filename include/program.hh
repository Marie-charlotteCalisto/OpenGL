#pragma once

#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "ogl.hh"

class Program {
public:
    Program() = default;
    ~Program() {if (log) free(log);}

    static Program *make_program(std::string vertex_shader_file,
            std::string fragment_shader_file,
            std::string geometry_shader_file);


    static Program *make_program(std::string vertex_shader_file,
            std::string fragment_shader_file);


    int getID() {return id;}
    char *get_log();
    bool is_ready();
    void use();
    void setUniform3f(const char *name, float a, float b, float c);
    void setUniformMatrix4fv(const char *name, GLsizei count,
                                      GLboolean transpose,
                                      const GLfloat *value);

private:
    char *log = nullptr;
    int id;
};
