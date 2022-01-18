#include <iostream>

#include "mouse.hh"

glm::vec3 position = glm::vec3(0, 5, -10);
float nb_frag = 1.0f;
float wind_power = 1.0f;

float get_wind_power(GLFWwindow *win)
{
    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS){
        wind_power += 0.05f;
    }
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS){
        wind_power -= 0.05f;
    }
    if (glfwGetKey(win, GLFW_KEY_R) == GLFW_PRESS){
        wind_power = 1;
    }
    return wind_power;
}


float get_nb_frag(GLFWwindow *win)
{
    if (glfwGetKey(win, GLFW_KEY_P) == GLFW_PRESS){
        nb_frag += 0.5f;
    }

    if (glfwGetKey(win, GLFW_KEY_M) == GLFW_PRESS){
        nb_frag -= 1;
    }
    return nb_frag;
}

glm::mat4 getViewMatrix(GLFWwindow *win) {

    double mousex, mousey;
    int width, height;
    glfwGetCursorPos(win, &mousex, &mousey);
    glfwGetWindowSize(win, &width, &height);

    float horizontalAngle = 0.002 * float(width / 2 - mousex);
    float verticalAngle = 0.002 * float(height / 2 - mousey);

    glm::vec3 direction = glm::vec3(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    glm::vec3 right = glm::vec3(
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        cos(horizontalAngle - 3.14f/2.0f)
    );

    direction = 0.6f * glm::normalize(direction);
    right = 0.07f * glm::normalize(right);
    glm::vec3 up = glm::cross(right, direction);


    // Move forward
    if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS){
        position += direction;
    }

    // Move backward
    if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS){
        position -= direction;
    }

    // Strafe right
    if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS){
        position += right;
    }

    // Strafe left
    if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS){
        position -= right;
    }
    return glm::lookAt(position, position + direction, up);

}

glm::mat4 getProjectionMatrix() {
    return glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 150.0f);


}
