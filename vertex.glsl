#version 330 core

layout(location = 0) in vec3 aPos;

out vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;

void main()
{
    texCoord = normalize(aPos.xy);
    gl_Position = projection * view * transform * vec4(aPos, 1);
}