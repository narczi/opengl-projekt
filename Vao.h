#pragma once
class Vao
{
public:

	Vao(unsigned int* VAO, unsigned int* VBO, float *vertices, size_t data_size);

	void bind(unsigned int* VAO);
	void unbind();
};

