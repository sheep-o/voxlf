#ifndef ENGINE_MESHBUILDER_H
#define ENGINE_MESHBUILDER_H

#include "Mesh.h"

class MeshBuilder {
public:
    std::vector<unsigned int> BuildCube(char meshCode);
private:
    const std::vector<float> m_CubeVerts = {
            -1, -1,  1, //0
            1, -1,  1, //1
            -1,  1,  1, //2
            1,  1,  1, //3
            -1, -1, -1, //4
            1, -1, -1, //5
            -1,  1, -1, //6
            1,  1, -1  //7
    };

    const std::vector<unsigned int> m_BottomIndices = {
            0, 2, 3,
            0, 1, 3,
    };
    const std::vector<unsigned int> m_TopIndices = {
            4, 6, 7,
            4, 5, 7
    };
    const std::vector<unsigned int> m_LeftIndices = {
            1, 3, 7,
            1, 5, 7,
    };
    const std::vector<unsigned int> m_RightIndices = {
            0, 2, 6,
            0, 4, 6,
    };
    const std::vector<unsigned int> m_FrontIndices = {
            0, 4, 5,
            0, 1, 5,
    };
    const std::vector<unsigned int> m_BackIndices = {
            2, 6, 7,
            2, 3, 7,
    };

    const std::vector<std::vector<unsigned int>> m_FaceOrder = {
            m_BottomIndices,
            m_TopIndices,
            m_LeftIndices,
            m_RightIndices,
            m_FrontIndices,
            m_BackIndices
    };
};


#endif //ENGINE_MESHBUILDER_H
