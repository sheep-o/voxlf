//
// Created by sheep on 12/22/22.
//

#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include <GL/glew.h>

#include "Window.h"
#include "ShaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera {
public:
    Camera(float fov, float aspectRatio, glm::vec3 eye, glm::vec3 center, ShaderProgram* program, Window* window);
    void CalculateView(float deltaTime);

    glm::mat4 m_View;
    glm::mat4 m_Projection;
    glm::vec3 m_Pos;
    glm::vec3 m_ChunkPos;

    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;

    float m_MoveSpeed;
    float m_LookSpeed;
    float m_FOV;

    Window* m_pWindow;
    ShaderProgram* m_pProgram;

    const int CHUNK_WIDTH = 4;
    const int CHUNK_RADIUS = 2;
private:
    double oldX = 0, oldY = 0, yaw = 0, pitch = 0;
};


#endif //ENGINE_CAMERA_H
