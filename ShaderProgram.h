//
// Created by sheep on 12/22/22.
//

#ifndef ENGINE_SHADERPROGRAM_H
#define ENGINE_SHADERPROGRAM_H


class ShaderProgram
{
public:
    ShaderProgram(const char* vPath, const char* fPath);
    void Use();
    int GetUniformLocation(const char* name);
    void SendMat4(const char* name, float mat[], bool transpose);

    unsigned int m_ID;
};


#endif //ENGINE_SHADERPROGRAM_H
