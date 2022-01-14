#include "model.hh"
void Model::Draw(glm::mat4 projection, glm::mat4 view, GLuint matID)
{
    glm::mat4 transform = glm::scale(glm::mat4(1.f), glm::vec3(scale));
    transform = glm::translate(transform, glm::vec3(xo, 0, yo));
    glm::mat4 mvp = projection * view * transform;
    shader->use();
    shader->setUniformMatrix4fv("MVP", 1, GL_FALSE, &mvp[0][0]);
    shader->setUniformMatrix4fv("model_view", 1, GL_FALSE, &view[0][0]);

    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].draw(shader->is_triangles());
}
void Model::loadModel(const char *path, std::vector<std::string> texture_path)
{
    bool res = loadOBJ(path, meshes);

    GLuint vaoIDs[10];
    glGenVertexArrays(meshes.size(), &vaoIDs[0]);
    TEST_OPENGL_ERROR();

    auto textures = getTextures(texture_path);
    for (int i = 0; i < meshes.size(); i++) {
        glBindVertexArray(vaoIDs[i]);
        meshes[i].setup(vaoIDs[i]);
        if (i < textures.size())
        {
            meshes[i].setTexture(textures[i]);
        }
    }
}
