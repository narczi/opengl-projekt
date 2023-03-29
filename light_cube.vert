#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightDir;

out vec3 color;

float directionalLight(vec3 lightDir, vec3 normal) {
    float f = dot(normalize(normal), -lightDir);
    if (f > 0)
        return f;
    else
        return 0.0;
}

void main()
{
    vec3 normal = mat3(transpose(inverse(model))) * aNormal;
    float light = directionalLight(lightDir, normal);

    color = vec3(light, light, light);
    //color = normal;
    //color = vec3(aTexCoord, 0.0);

    gl_Position = projection * view * model * vec4(aPos, 1.0);
};
