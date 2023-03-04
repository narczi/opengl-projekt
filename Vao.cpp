#include "Vao.h"

#include <glad/glad.h>

#include <iostream>

Vao::Vao(unsigned int *VAO, unsigned int* VBO, float *vertices, size_t data_size){
	glBindVertexArray(*VAO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, data_size, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Vao::bind(unsigned int* VAO)
{
	glBindVertexArray(*VAO);
}

void Vao::unbind()
{
	glBindVertexArray(0);
}