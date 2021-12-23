#include <iostream>
#include "mesh.hh"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

Texture::Texture(const char *path) {
        int width, height, nrChannels;
       // unsigned int textureID;
        glGenTextures(1, &textureID);
        unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (!data)
        {
            std::cout << "Texture fail loading path : " << path << std::endl;
            stbi_image_free(data);
            return;
        }
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(2);

        stbi_image_free(data);
}

std::vector<Texture> getTextures(std::vector<std::string> texture_path)
{
    std::vector<Texture> textures;
    for (int i = 0; i < texture_path.size(); i++)
        textures.push_back(Texture(texture_path[i].c_str()));

    return textures;
}


void Mesh::setup(GLuint vao) {
    GLuint vbuffer, nbuffer, uvbuffer;
    glGenBuffers(1, &vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    // Load normals into a VBO
    glGenBuffers(1, &nbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, nbuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    if (uvCoord.size() > 0)
    {
        // Load uvCoords into a VBO
        glGenBuffers(1, &uvbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glBufferData(GL_ARRAY_BUFFER, uvCoord.size() * sizeof(glm::vec2), &uvCoord[0], GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(2);
    }
    this->vao = vao;
}

void Mesh::draw() const {
    glBindTexture(GL_TEXTURE_2D, texture.textureID);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}

void Mesh::setTexture(Texture text) {
    texture = text;
}
