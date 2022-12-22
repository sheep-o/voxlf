#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Window.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Mesh.h"

int main() {
    Window window(1280, 720, "Window");

    ShaderProgram program("../vertex.glsl", "../fragment.glsl");
    program.Use();

    std::vector<float> verts = {
            -1, -1,  1, //0
            1, -1,  1, //1
            -1,  1,  1, //2
            1,  1,  1, //3
            -1, -1, -1, //4
            1, -1, -1, //5
            -1,  1, -1, //6
            1,  1, -1,  //7
    };

    std::vector<unsigned int> indices = {
            //Top
            2, 6, 7,
            2, 3, 7,

            //Bottom
            0, 4, 5,
            0, 1, 5,

            //Left
            0, 2, 6,
            0, 4, 6,

            //Right
            1, 3, 7,
            1, 5, 7,

            //Front
            0, 2, 3,
            0, 1, 3,

            //Back
            4, 6, 7,
            4, 5, 7
    };

    Camera cam(30.f, 1280.f / 720.f,
               glm::vec3(0, 0, 5), glm::vec3(0, 0, 0),
               &program, &window);

    glEnable(GL_DEPTH_TEST);

    float currentFrame = 0, deltaTime = 0, lastFrame = 0;

    char chunk[2][2] = {
            {1, 1},
            {1, 1},
    };

    std::vector<Mesh*> meshes = {};

    for (int z = 0; z < sizeof(chunk); z += 2) {
        for (int x = 0; x < sizeof(chunk); x += 2) {
            meshes.push_back(new Mesh(verts, indices, glm::vec3(x, 0, z)));
        }
    }



    while (!window.ShouldClose()) {
        currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        cam.CalculateView(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1, 0, 0, 1);

        for (Mesh* mesh : meshes) {
            mesh->Bind();
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

            glm::mat4 transform(1);
            transform = glm::translate(transform, mesh->m_Pos);

            program.SendMat4("transform", glm::value_ptr(transform), false);
        }

        window.SwapBuffers();
        glfwPollEvents();
    }
}
