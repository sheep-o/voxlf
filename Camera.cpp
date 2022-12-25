//
// Created by sheep on 12/22/22.
//

#include "Camera.h"
#include <cstdio>
#include <iostream>

Camera::Camera(float fov, float aspectRatio, glm::vec3 eye, glm::vec3 center, ShaderProgram* program, Window* window) {
    glfwSetInputMode(window->m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    m_Front = glm::vec3(0, 0, -1);
    m_Up = glm::vec3(0, 1, 0);
    m_Right = glm::vec3(1, 0, 0);

    m_MoveSpeed = 15.f;
    m_LookSpeed = 5.f;

    m_Projection = glm::perspective(glm::radians(fov), aspectRatio, .1f, 1000.f);
    program->SendMat4("projection", glm::value_ptr(m_Projection), false);

    m_Pos = eye;
    m_View = glm::lookAt(m_Pos, center, glm::vec3(0, 1, 0));
    program->SendMat4("view", glm::value_ptr(m_View), false);

    m_pWindow = window;
    m_pProgram = program;
    m_FOV = fov;
}

void Camera::CalculateView(float deltaTime) {
    // movement
    if (m_pWindow->GetKey(GLFW_KEY_W)) {
        m_Pos += m_Front * m_MoveSpeed * deltaTime;
    }
    if (m_pWindow->GetKey(GLFW_KEY_S)) {
        m_Pos -= m_Front * m_MoveSpeed * deltaTime;
    }
    if (m_pWindow->GetKey(GLFW_KEY_D)) {
        m_Pos += glm::normalize(glm::cross(m_Front, m_Up)) * m_MoveSpeed * deltaTime;
    }
    if (m_pWindow->GetKey(GLFW_KEY_A)) {
        m_Pos -= glm::normalize(glm::cross(m_Front, m_Up)) * m_MoveSpeed * deltaTime;
    }
    if (m_pWindow->GetKey(GLFW_KEY_F1)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if (m_pWindow->GetKey(GLFW_KEY_ESCAPE)) {
        glfwSetInputMode(m_pWindow->m_pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    if (m_pWindow->GetMouse(0)) {
        glfwSetInputMode(m_pWindow->m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }


    int chunkX = floor(m_Pos.x / (float)CHUNK_WIDTH);
    int chunkZ = floor(m_Pos.z / (float)CHUNK_WIDTH);

    m_ChunkPos.x = chunkX;
    m_ChunkPos.z = chunkZ;

//    printf("Position: (%f, y, %f) | Chunk: (%d, ?, %d)\n", m_Pos.x, m_Pos.z, chunkX, chunkZ);

    // camera look
    double x, y;
    glfwGetCursorPos(m_pWindow->m_pWindow, &x, &y);

    float dX = (float)(oldX - x);
    float dY = (float)(oldY - y);

    yaw -= dX * m_LookSpeed * deltaTime;
    pitch += dY * m_LookSpeed * deltaTime;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    if (yaw >= 360 || yaw <= -360)
        yaw = 0;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    m_Front = glm::normalize(direction);

    oldX = x;
    oldY = y;

    m_View = glm::lookAt(m_Pos, m_Pos + m_Front, glm::vec3(0, 1, 0));
    m_pProgram->SendMat4("view", glm::value_ptr(m_View), false);
}