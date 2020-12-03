#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;

#ifndef __glad_h_
#include <glad\glad.h>
#endif

class Triangle
{
public:
    //顶点数据
    float vertices[9] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    };

    const char* vertexShaderSource;    //顶点着色器
    const char* pixelShaderSource;     //像素着色器

    int shaderProgram;                 //着色器程序
    unsigned int VBO;                  //顶点缓存对象
    unsigned int VAO;                  //顶点数组对象

    //渲染属性
    GLenum renderMode = GL_FILL;        //渲染模式

    //log变量
    int shaderCompileSuc;     //Shader编译是否成功
    int shaderLinkSuc;        //Shader链接是否成功
    char infoLog[512];        //Log数组

public:
	Triangle();
    Triangle(GLenum _rendermode);

    void SetVertexShader();
    void SetPixelShader();
    void PrepareData();  //准备数据
	void Rendering();    //渲染
    void DeleteData();
};

