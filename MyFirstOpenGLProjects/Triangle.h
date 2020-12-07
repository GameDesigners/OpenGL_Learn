#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;

#ifndef __glad_h_
#include <glad\glad.h>
#endif

#include "Shader.h"

class Triangle
{
public:
    //顶点数据
    float vertices[18] = {
        -0.5f, -0.5f, 0.0f,1.0f,0.0f,0.0f, // left  
         0.5f, -0.5f, 0.0f, 0.0f,1.0f,0.0f,// right 
         0.0f,  0.5f, 0.0f,0.0f,0.0f,1.0f  // top   
    };

    unsigned int VBO = NULL;                  //顶点缓存对象
    unsigned int VAO = NULL;                  //顶点数组对象

    //渲染属性
    GLenum renderMode = GL_FILL;        //渲染模式

public:
	Triangle(string _vetexFilePath, string _fragmentFilePath);
    Triangle(string _vetexFilePath, string _fragmentFilePath,GLenum _rendermode);

    void PrepareData();  //准备数据
	void Rendering();    //渲染
    void DeleteData();

private:
    Shader* ourShader;
};

