#version 330 core

layout(location = 0) in vec3 aPos;

out vec3 pos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;

void main()
{
    gl_Position = projection * view * transform * vec4(aPos, 1);
    pos = aPos;
}