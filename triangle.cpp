#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
using namespace std;
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* khidki = glfwCreateWindow(700, 700, "mera khud ka code", NULL, NULL);
	if (!khidki)
	{
		cout << "khidki nahi bana paaya";
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(khidki);
	gladLoadGL();
	glViewport(0, 0, 700, 700);
	float positions[] =
	{
		1.0f,0.0f,
		-1.0f,0.0f,
		0.0f,1.0f
	};
	unsigned VBO,VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	const string vertex_shader =
		"#version 330 core\n"
		"in vec2 positions;\n"
		"out vec2 color;\n"
		"void main()\n"
		"{\n"
		"gl_Position=vec4(positions,0.0f,1.0f);\n"
		"color=vec2(positions);\n"
		"}";
	const string fragment_shader =
		"#version 330 core\n"
		"out vec4 colors;\n"
		"in vec2 color;\n"
		"void main()\n"
		"{\n"
		"colors=vec4(color,0.0f,1.0f);\n"
		"}";
	const char* vertex = vertex_shader.c_str(),* fragment = fragment_shader.c_str();
	unsigned vert= glCreateShader(GL_VERTEX_SHADER), frag= glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vert, 1, &vertex,NULL);
	glCompileShader(vert);
	glShaderSource(frag, 1, &fragment, NULL);
	glCompileShader(frag);
	unsigned program=glCreateProgram();
	glAttachShader(program, vert);
	glAttachShader(program, frag);
	glLinkProgram(program);
	while (!glfwWindowShouldClose(khidki))
	{
		glUseProgram(program);
		glfwPollEvents();
		glClearColor(0.5f, 0.4f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(khidki);
	}
	glDeleteProgram(program);
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteShader(vert);
	glDeleteShader(frag);
	glfwTerminate();
	return 0;
}
