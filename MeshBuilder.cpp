//
// Created by sheep on 12/20/22.
//

#include <climits>
#include "MeshBuilder.h"

std::vector<unsigned int> indices = {};

std::vector<unsigned int> MeshBuilder::BuildCube(char meshCode)
{
    indices.clear();

    char bit;
    for (char i = sizeof(meshCode) * CHAR_BIT - 3; i >= 0; --i)
    {
        bit = (meshCode >> i) & 1;
        if (bit)
        {
//            std::merge(indices.begin(), indices.end(),
//                       m_FaceOrder[i].begin(), m_FaceOrder[i].end(),
//                       std::back_inserter(indices));
            for (int j = 0; j < m_FaceOrder[i].size(); j++)
                indices.push_back(m_FaceOrder[i][j]);
        }
    }

    return indices;
}