#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 TriColor;
out vec4 vertexColor;
uniform float offset;
out vec3 verPos;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos.x + offset, aPos.y, aPos.z, 1.0);
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
    TriColor = aColor;
    verPos = aPos;
    TexCoord = aTexCoord;
};
