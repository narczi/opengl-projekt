#version 330 core

in vec3 TriColor;
out vec4 FragColor;
in vec3 verPos;

void main()
{
	FragColor = vec4(verPos, 1.0);
};