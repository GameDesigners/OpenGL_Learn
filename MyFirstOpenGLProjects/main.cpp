#include<iostream>
#include<GLAD/glad.h>
#include<glfw3.h>

#include "Triangle.h"
#include "Edge.h"

using namespace std;

/// <summary>
/// 回调函数,当窗口大小改变时调用
/// </summary>
/// <param name="window"></param>
/// <param name="width"></param>
/// <param name="height"></param>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/// <summary>
/// 处理Input事件
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

	//初始化GLAD
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
	//渲染循环
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		//渲染指令
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);    //颜色清空屏幕
		glClear(GL_COLOR_BUFFER_BIT);

		//创建一个Triangle并渲染出来
		//triangle.Rendering();
		edge.Rendering();
		//检查并调用事件，交换缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	triangle.DeleteData();
	edge.DeleteData();

	glfwTerminate();
	return 0;
}