#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

auto getProgramiv_ptr = &glGetProgramiv;
void ProgramErrorHandling(PFNGLGETPROGRAMIVPROC GetProgramParameter, GLuint program, int prog_param);
void ShaderErrorHandling(PFNGLGETSHADERIVPROC GetShaderParameter, GLuint shader, int shader_param);
const char* load_shader_src(string filename);

const char* vertexShaderSource = load_shader_src("primary.vert");
const char* fragmentShaderSourceOrange = load_shader_src("orange.frag");
const char* fragmentShaderSourceYellow = load_shader_src("yellow.frag");

int main() {
	// ------------------ WINDOW ------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);

	// ------------------ VERTEX SHADERS ------------------
	// Vertex Shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	ShaderErrorHandling(glGetShaderiv, vertexShader, GL_COMPILE_STATUS);
	// ------------------ FRAGMENT SHADERS ------------------
	// Orange Fragment Shader 
	unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSourceOrange, NULL);
	glCompileShader(fragmentShaderOrange);
	ShaderErrorHandling(glGetShaderiv, fragmentShaderOrange, GL_COMPILE_STATUS);
	// Yellow Fragment Shader 
	unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
	glCompileShader(fragmentShaderYellow);
	ShaderErrorHandling(glGetShaderiv, fragmentShaderYellow, GL_COMPILE_STATUS);

	// Shader Program object
	unsigned int shaderProgramOrange = glCreateProgram();
	unsigned int shaderProgramYellow = glCreateProgram();
	// Orange Program
	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
	glLinkProgram(shaderProgramOrange);
	// Yellow Program
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);

	ProgramErrorHandling(glGetProgramiv, shaderProgramOrange, GL_LINK_STATUS);
	ProgramErrorHandling(glGetProgramiv, shaderProgramYellow, GL_LINK_STATUS);

	float vertices_triangle_one[] =
	{
		-1.0f, -0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f, -0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	float vertices_triangle_two[] =
	{
		-1.0f, -1.0f, 0.0f, // vertex bottom-left
		 0.0f, -1.0f, 0.0f, // vertex bottom-right
		-0.5f,  0.0f, 0.0f, // vertex top
	};

	float vertices_square[] =
	{
		 0.5f,  0.5f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f // top left
	};
	float colors_square[] =
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f
	};
	unsigned int indices_square[] =
	{ // note that we start from 0!
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};

	float square[] = {
		// positions // colors // texture coords
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
	};

	// Vertex Array Object  (VAO)
	unsigned int VAOs[3], VBOs[3], EBO;
	glGenVertexArrays(3, VAOs);
	glGenBuffers(3, VBOs);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle_one), vertices_triangle_one, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle_two), vertices_triangle_two, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Element Buffer Object (EBO)
	glBindVertexArray(VAOs[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_square), vertices_square, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square), indices_square, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// activate 
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderOrange);

	Shader ourShader("primary.vert", "yellow.frag");
	Shader TriShader("primary.vert", "orange.frag");

	float timeValue;
	float greenValue;
	int vertexColorLocation;

	// TEXTURES
	float texCoords[] = {
		1.0f, 1.0f, //top-right corner
		1.0f, 0.0f, //lower-right corner
		0.0f, 0.0f, //lower-left corner
		0.0f, 1.0f, //top-left corner
	};

	

	unsigned int texture; 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load texture" << endl;
	}
	
	stbi_image_free(data);

	while (!glfwWindowShouldClose(window)) 
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		TriShader.use();
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		timeValue = glfwGetTime();
		greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		vertexColorLocation = glGetUniformLocation(shaderProgramYellow, "ourColor");
		ourShader.use();
		ourShader.setColor("ourColor", 0.0f, greenValue, 0.0f);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAOs[2]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(shaderProgramOrange);
	glDeleteProgram(shaderProgramYellow);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
		glfwSetWindowShouldClose(window, true);
}

void ProgramErrorHandling(PFNGLGETPROGRAMIVPROC GetProgramParameter, GLuint program, int prog_param) {
	int success;
	GetProgramParameter(program, prog_param, &success);

	char infoLog[512];
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINKING::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void ShaderErrorHandling(PFNGLGETSHADERIVPROC GetShaderParameter, GLuint shader, int shader_param) {
	int success;
	int shader_type;
	GetShaderParameter(shader, shader_param, &success);

	char infoLog[512];
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		glGetShaderiv(shader, GL_SHADER_TYPE, &shader_type);
		if (shader_type == GL_VERTEX_SHADER) {
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		else if (shader_type == GL_FRAGMENT_SHADER) {
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}
}

const char* load_shader_src(string filename) {
	string full_file;
	string line;
	ifstream opened_file(filename);

	while (getline(opened_file, line)) {
		full_file = full_file + line + "\n";
	}

	char* cstr = new char[full_file.length() + 1];
	strcpy(cstr, full_file.c_str());

	return cstr;
}

// PFNGLGETPROGRAMIVPROC
// void (*GetProgramParameter)(GLuint, GLenum, GLint)