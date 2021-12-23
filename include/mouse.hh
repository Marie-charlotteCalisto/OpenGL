#pragma once

#include "ogl.hh"

glm::mat4 getViewMatrix(GLFWwindow *win);

glm::mat4 getProjectionMatrix();

void mouse_pressed_callback(GLFWwindow* window, int button, int action, int mods);
