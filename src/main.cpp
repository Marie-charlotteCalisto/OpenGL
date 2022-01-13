#include <filesystem>

#include "ogl.hh"
#include "program.hh"
#include "objloader.hh"
#include "mouse.hh"
#include "model.hh"
#include "stb_image.h"
#include "skybox.hh"


GLFWwindow *window;

std::vector<Model> models;
std::vector<Model> models_anim;
glm::mat4 projection;
GLuint matID;
int width = 1024;
int height =768;

bool initGlew() {
    if (glewInit())
    {
        std::cerr << "Error while initializing glew" << std::endl;
        return false;
    }
    return true;
}

void init_GL() {
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glClearColor(0.4,0.4,0.4,1.0);
}


void window_resize_callback(GLFWwindow* window, int width, int height)
{
    glfwSetWindowSize(window, width, height);
}


bool initGLFW() {
    if( !glfwInit() )
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(width, height, "grass", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window.");
        getchar();
        glfwTerminate();
        return false;
    }
 //   glfwSetWindowSizeCallback(window, window_resize_callback);
//glfwSetWindowContentScaleCallback(window, window_content_scale_callback);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    return true;
}


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
void init_skybox_buffer(unsigned int &skyboxVAO, unsigned int &skyboxVBO)
{
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void draw_sky(Program *sky_shader, unsigned int skyboxVAO, unsigned int cubemapTexture)
{
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
}
bool init_shaders()
{
    std::vector<std::pair<GLenum, std::string>> plane_shader_path = {
        {GL_VERTEX_SHADER, ROOT_DIR "/shaders/vertex_nothing.glsl"},
        {GL_TESS_CONTROL_SHADER, ROOT_DIR "/shaders/tesselation_control.glsl"},
        {GL_TESS_EVALUATION_SHADER, ROOT_DIR "/shaders/tesselation_eval.glsl"},
        {GL_GEOMETRY_SHADER, ROOT_DIR "/shaders/geometry_mesh.glsl"},
        {GL_FRAGMENT_SHADER, ROOT_DIR "/shaders/fragment_color.glsl"}};

    std::vector<std::pair<GLenum, std::string>> cube_shader_path = {
        {GL_VERTEX_SHADER, ROOT_DIR "/shaders/vertex_nothing.glsl"},
        {GL_TESS_CONTROL_SHADER, ROOT_DIR "/shaders/tesselation_control.glsl"},
        {GL_TESS_EVALUATION_SHADER, ROOT_DIR "/shaders/tesselation_eval.glsl"},
        {GL_GEOMETRY_SHADER, ROOT_DIR "/shaders/geometry_mesh.glsl"},
        {GL_FRAGMENT_SHADER, ROOT_DIR "/shaders/fragment_color.glsl"}};




    std::vector<std::pair<GLenum, std::string>> sky_shader_path = {
        {GL_VERTEX_SHADER, ROOT_DIR "/shaders/vertex_sky_shader.glsl"},
        {GL_FRAGMENT_SHADER, ROOT_DIR "/shaders/sky_shader.glsl"}};

    Program *plane_shader = Program::make_program(plane_shader_path);
    Program *cube_shader = Program::make_program(cube_shader_path);
    Program *sky_shader = Program::make_program(sky_shader_path);

    plane_shader->use();
    plane_shader->setUniform3f("lightPosition", -5.f, 100.f, -40.f);

    cube_shader->use();
    cube_shader->setUniform3f("lightPosition", -5.f, 100.f, -40.f);

    sky_shader->use();

    unsigned int skyboxVAO, skyboxVBO;
    init_skybox_buffer(skyboxVAO, skyboxVBO);


    unsigned int cubemapTexture = loadCubemap(faces);

    std::vector<std::string> cube_textures = {
        ROOT_DIR "/texture/cube.jpg",
    };
    Model plane(ROOT_DIR "/obj/plane.obj", {}, plane_shader, 1, 0, 0);
    models.push_back(plane);

    Model cube(ROOT_DIR "/obj/cube.obj", cube_textures, cube_shader, 1, 0, 0);
    models.push_back(cube);

    glfwSetCursorPos(window, 200, 200);


    projection = getProjectionMatrix();
    int frame = 0;
    int i = frame;
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        display(projection);

        draw_sky(sky_shader, skyboxVAO, cubemapTexture);
        i--;
        if (i <= 0)
            i = frame;
    }

    glfwTerminate();
    return true;

}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei length, const GLchar* message, const void* userParam)
{
    (void) source;
    (void) id;
    (void) length;
    (void) userParam;

    if (type == GL_DEBUG_TYPE_ERROR)
        std::cerr << "** GL_ERROR **" << " type = 0x" << type\
            << " severity = 1x" << severity\
            << ", message = " << message << std::endl;
}



int main(int argc, char** argv) {
    initGLFW();
    if (!initGlew())
        std::exit(-1);
    init_GL();
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, nullptr);
    init_shaders();
    return 0;
}
