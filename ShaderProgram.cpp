#include "ShaderProgram.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <vector>

ShaderProgram::ShaderProgram(const char* vPath, const char* fPath)
{
    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vShaderSource;
    std::ifstream vShaderStream(vPath, std::ios::in);
    if (vShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << vShaderStream.rdbuf();
        vShaderSource = sstr.str();
        vShaderStream.close();
    }
    else
    {
        fprintf(stderr, "Failed to open vertex shader source file.\n");
    }

    const char* c_vShaderSource = vShaderSource.c_str();
    glShaderSource(vShader, 1, &c_vShaderSource, nullptr);
    glCompileShader(vShader);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> error(InfoLogLength + 1);
        glGetShaderInfoLog(vShader, InfoLogLength, NULL, &error[0]);
        printf("%s\n", &error[0]);
    }
    else
    {
        printf("Successfully compiled vertex shader.\n");
    }

    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fShaderSource;
    std::ifstream fShaderStream(fPath, std::ios::in);
    if (fShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << fShaderStream.rdbuf();
        fShaderSource = sstr.str();
        fShaderStream.close();
    }
    else
    {
        fprintf(stderr, "Failed to open fragment shader source file.\n");
    }

    const char* c_fShaderSource = fShaderSource.c_str();
    glShaderSource(fShader, 1, &c_fShaderSource, nullptr);
    glCompileShader(fShader);

    glGetShaderiv(fShader, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(fShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> error(InfoLogLength + 1);
        glGetShaderInfoLog(fShader, InfoLogLength, NULL, &error[0]);
        printf("%s\n", &error[0]);
    }
    else
    {
        printf("Successfully compiled fragment shader.\n");
    }

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vShader);
    glAttachShader(m_ID, fShader);
    glLinkProgram(m_ID);

    // Check the program
    glGetProgramiv(m_ID, GL_LINK_STATUS, &Result);
    glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(m_ID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(m_ID, vShader);
    glDetachShader(m_ID, fShader);

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

void ShaderProgram::Use()
{
    glUseProgram(m_ID);
}

int ShaderProgram::GetUniformLocation(const char* name)
{
    return glGetUniformLocation(m_ID, name);
}

void ShaderProgram::SendMat4(const char* name, float mat[], bool transpose)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, transpose, mat);
}