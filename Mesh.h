//
// Created by sheep on 12/22/22.
//

#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H

#include <vector>

#include "glm/vec3.hpp"

class Mesh {
public:
    Mesh(std::vector<float> vertices, std::vector<unsigned int> indices);
    Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, glm::vec3 pos);
    void Bind();
    unsigned int VAO, VBO, EBO;
    glm::vec3 m_Pos;
};


#endif //ENGINE_MESH_H
