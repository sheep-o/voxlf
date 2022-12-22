//
// Created by sheep on 12/22/22.
//

#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, const char* title);
    void SwapBuffers();
    bool ShouldClose();
    bool GetKey(int key);
    bool GetMouse(int btn);

    GLFWwindow* m_pWindow;
};


#endif //ENGINE_WINDOW_H
