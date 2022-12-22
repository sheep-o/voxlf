//
// Created by sheep on 12/22/22.
//

#include "Window.h"
#include <cstdio>

Window::Window(int width, int height, const char *title) {
    if (!glfwInit()) fprintf(stderr, "Failed to initialize GLFW");

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_pWindow = glfwCreateWindow(1280, 720, "Window", 0, 0);
    if (!m_pWindow) fprintf(stderr, "Failed to create a window");

    glfwMakeContextCurrent(m_pWindow);

    if (glewInit() != GLEW_OK) fprintf(stderr, "Failed to initialize GLEW");
}

void Window::SwapBuffers() {
    glfwSwapBuffers(m_pWindow);
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(m_pWindow);
}

bool Window::GetKey(int key) {
    return glfwGetKey(m_pWindow, key) == GLFW_PRESS;
}

bool Window::GetMouse(int btn) {
    return glfwGetMouseButton(m_pWindow, btn) == GLFW_PRESS;
}
