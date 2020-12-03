#include<iostream>
#include<GLAD/glad.h>
#include<glfw3.h>

#include "Triangle.h"
#include "Edge.h"

using namespace std;

/// <summary>
/// �ص�����,�����ڴ�С�ı�ʱ����
/// </summary>
/// <param name="window"></param>
/// <param name="width"></param>
/// <param name="height"></param>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/// <summary>
/// ����Input�¼�
/// </summary>
/// <param name="window"></param>
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window,true);
}

int main()
{
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

	//��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Triangle triangle;
	triangle.PrepareData();

	Edge edge(GL_LINE);
	edge.PrepareData();
	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		//��Ⱦָ��
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);    //��ɫ�����Ļ
		glClear(GL_COLOR_BUFFER_BIT);

		//����һ��Triangle����Ⱦ����
		//triangle.Rendering();
		edge.Rendering();
		//��鲢�����¼�����������
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	triangle.DeleteData();
	edge.DeleteData();

	glfwTerminate();
	return 0;
}