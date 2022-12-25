#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "FastNoiseLite.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define GLT_IMPLEMENTATION
#include "gltext.h"

#include "Window.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Mesh.h"

#include <cmath>
#include <random>

#define CHECK_BIT(var,pos) (((var)>>(pos)) & 1)

int main() {
    Window window(1280, 720, "Window");

    ShaderProgram program("../vertex.glsl", "../fragment.glsl");
    program.Use();

    const std::vector<float> verts = {
            -1, -1,  1, //0
            1, -1,  1, //1
            -1,  1,  1, //2
            1,  1,  1, //3
            -1, -1, -1, //4
            1, -1, -1, //5
            -1,  1, -1, //6
            1,  1, -1  //7
    };

    const std::vector<unsigned int> indices = {
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3
    };

    Camera cam(30.f, 1280.f / 720.f,
               glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),
               &program, &window);

    glEnable(GL_DEPTH_TEST);

    float currentFrame = 0, deltaTime = 0, lastFrame = 0;

    std::vector<Mesh*> meshes = {};
    meshes.push_back(new Mesh(verts, indices, glm::vec3(0)));

    glm::vec3 lastChunkPos = cam.m_ChunkPos;

    // buffer for text
    char buf[1024];

    // init noise
    FastNoiseLite fn;
    fn.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
// set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// load and generate the texture
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../brogan.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glActiveTexture(GL_TEXTURE0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Failed to load texture\n");
    }

    while (!window.ShouldClose()) {
        currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        cam.CalculateView(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0.72f, 1.f, 1.f);

//         if player has entered a new chunk
        if (lastChunkPos != cam.m_ChunkPos) {
            // free all old meshes

            for (int i = 0; i < meshes.size(); i++) {
                delete meshes[i];
            }
            meshes.clear();

//            // generate data for new chunk
//            char chunk[cam.CHUNK_WIDTH][cam.CHUNK_WIDTH];
//            memset( &chunk[0][0], 63, sizeof(chunk) );

            for (int cz = -cam.CHUNK_RADIUS / 2.f; cz < cam.CHUNK_RADIUS / 2.f; cz++) {
                for (int cx = -cam.CHUNK_RADIUS / 2.f; cx < cam.CHUNK_RADIUS / 2.f; cx++) {
                    for (int z = 0; z < cam.CHUNK_WIDTH; z++) {
                        for (int x = 0; x < cam.CHUNK_WIDTH; x++) {
                            float realX = x + (cam.CHUNK_WIDTH * cam.m_ChunkPos.x) + (cam.CHUNK_WIDTH * cx);
                            float realZ = z + (cam.CHUNK_WIDTH * cam.m_ChunkPos.z) + (cam.CHUNK_WIDTH * cz);
                            float y = fn.GetNoise(realX * 10, realZ * 3);
                            meshes.push_back(new Mesh(verts, 63, glm::vec3(realX, round(y), realZ)));
                        }
                    }
                }
            }

            //
        }

        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE0);
        // draw all meshes in queue
        for (Mesh* mesh : meshes) {
            mesh->Bind();
            glDrawElements(GL_TRIANGLES, mesh->m_IndexCount, GL_UNSIGNED_INT, 0);

            glm::mat4 transform(1);
            transform = glm::translate(transform, mesh->m_Pos);
            transform = glm::scale(transform, glm::vec3(0.5f));
            program.SendMat4("transform", glm::value_ptr(transform), false);
        }

        lastChunkPos = cam.m_ChunkPos;

        // Initialize glText
        gltInit();

// Creating text
        GLTtext *text = gltCreateText();

        sprintf(buf, "Pos:     %f, %f, %f\nChunk: %f, %f, %f\nFPS:     %f", cam.m_Pos.x, cam.m_Pos.y, cam.m_Pos.z, cam.m_ChunkPos.x, 0.f, cam.m_ChunkPos.z, 1/deltaTime);
        gltSetText(text, buf);

// Begin text drawing (this for instance calls glUseProgram)
        gltBeginDraw();

// Draw any amount of text between begin and end
        gltColor(1.0f, 1.0f, 1.0f, 1.0f);
        gltDrawText2D(text, 10, 10, 1.2f);

// Finish drawing text
        gltEndDraw();

// Deleting text
        gltDeleteText(text);

// Destroy glText
        gltTerminate();

        program.Use();

        window.SwapBuffers();
        glfwPollEvents();
    }
}
