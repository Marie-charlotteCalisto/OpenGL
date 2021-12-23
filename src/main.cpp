#include "ogl.hh"
#include "program.hh"
#include "objloader.hh"
#include "mouse.hh"
#include "model.hh"
#include "stb_image.h"
#include <filesystem>

#define ROOT_DIR "../data"

GLFWwindow *window;

std::vector<Model> models;
std::vector<Model> models_anim;
GLuint matID;

unsigned int loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrComponents;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void display(glm::mat4 projection) {
    glm::mat4 view = getViewMatrix(window);
    for (auto model: models) {
        model.Draw(projection, view, matID);
    }
}
void display_anim(glm::mat4 projection, int frame) {

    glm::mat4 view = getViewMatrix(window);
    models_anim[frame].Draw(projection, view, matID);
    std::cout << frame << std::endl;
}

bool initGLFW() {
    if( !glfwInit() )
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(1024, 768, "Flowers", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window.");
        getchar();
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    return true;
}

bool initGlew() {
    return glewInit() == GLEW_OK;
}

int main(int argc, char** argv) {
    initGLFW();
    initGlew();
    glClearColor(0.0f, 0.3f, 0.6f, 0.0f);

    Program *cube_shader = Program::make_program(ROOT_DIR "/vertex_shader.glsl",
                                        ROOT_DIR "/fragment_shader.glsl",
                                        ROOT_DIR "/geometry_shader.glsl");
    Program *sky_shader = Program::make_program(ROOT_DIR "/vertex_sky_shader.glsl",
                                        ROOT_DIR "/sky_shader.glsl");

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    glm::mat4 projection = getProjectionMatrix();


    cube_shader->use();
    cube_shader->setUniform3f("lightPosition", -5.f, 100.f, -40.f);

    sky_shader->use();
    //sky_shader->setUniform3f("lightPosition", -5.f, 100.f, -40.f);

    float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };


    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    std::vector<std::string> faces
    {
        ROOT_DIR "/skybox/right.jpg",
        ROOT_DIR "/skybox/left.jpg",
        ROOT_DIR "/skybox/top.jpg",
        ROOT_DIR "/skybox/bottom.jpg",
        ROOT_DIR "/skybox/front.jpg",
        ROOT_DIR "/skybox/back.jpg",
    };
   unsigned int cubemapTexture = loadCubemap(faces);

    std::vector<std::string> cube_textures = {
        //ROOT_DIR "/rose/Models and Textures/grass_texture225.jpg",
    };
    Model cube(ROOT_DIR "/cube.obj", cube_textures, cube_shader, 4, 0, 0);
    models.push_back(cube);

    glfwSetCursorPos(window, 200, 200);

    int frame = 0;
    int i = frame;
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //display_anim(projection, i);
        display(projection);

        // draw skybox as last
        sky_shader->use();
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        glm::mat4 view = glm::mat4(glm::mat3(getViewMatrix(window)));
        glm::mat4 transform = glm::scale(glm::mat4(1.f), glm::vec3(1.0f));
        glm::mat4 mvp = projection * view * transform;
        sky_shader->setUniformMatrix4fv("MVP", 1, GL_FALSE, &mvp[0][0]);


        // skybox cube
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glBindVertexArray(skyboxVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default

        glfwSwapBuffers(window);
        glfwPollEvents();
        i--;
        if (i <= 0)
            i = frame;
    }

    glfwTerminate();
    return 0;
}
