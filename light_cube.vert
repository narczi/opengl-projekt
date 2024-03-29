#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;
out vec3 normal;
out vec3 position;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = vec2(0.0, 0.0);
    normal = mat3(transpose(inverse(model))) * aNormal;
    position = vec3(model * vec4(aPos, 1.0));
};
