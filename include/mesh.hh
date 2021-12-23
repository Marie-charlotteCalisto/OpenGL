#pragma once
#include <vector>

#include "ogl.hh"


struct Texture {
    Texture() = default;
    Texture(const char *path);

    GLuint textureID = 0;
};

std::vector<Texture> getTextures(std::vector<std::string> texture_path);

struct Mesh {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvCoord;
    Texture texture;

    Mesh() {
        vertices = std::vector<glm::vec3>();
        normals = std::vector<glm::vec3>();
    }

    void setup(GLuint vao);
    void draw() const;
    void setTexture(Texture text);

private:
    GLuint vao;
};
