#pragma once
#include<iostream>
#include<vector>
#include<string>
#include <glad\glad.h>
#include <glfw3.h>
using namespace std;

#include "Shader.h"
#include "Texture.h"

class Edge
{
public:
    //顶点数据
    float vertices[32] =
    {
    //  -----位置--------   -----颜色------  -纹理坐标-
        0.5f,  0.5f, 0.0f,  1.0f,0.0f,0.0f,  1.0f,1.0f,            // 右上角
        0.5f, -0.5f, 0.0f,  0.0f,1.0f,0.0f,  1.0f,0.0f,           // 右下角
       -0.5f, -0.5f, 0.0f,  0.0f,0.0f,1.0f,  0.0f,0.0f,           // 左下角
       -0.5f,  0.5f, 0.0f,  1.0f,1.0f,0.0f,  0.0f,1.0f           // 左上角
    };

    //索引数据
    unsigned int indices[6] =
    { 
        // 注意索引从0开始! 
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    unsigned int VBO;                  //顶点缓存对象
    unsigned int VAO;                  //顶点数组对象
    unsigned int EBO;                  //索引缓冲对象

    //渲染属性
    GLenum renderMode= GL_FILL;        //渲染模式


public:
    Edge(string _vetexFilePath, string _fragmentFilePath, string _texturePath);
    Edge(string _vetexFilePath, string _fragmentFilePath,GLenum _rendermode, string _texturePath);


    void PrepareData();  //准备数据
    void Rendering();    //渲染
    void DeleteData();

private:
    Shader* ourShader;
    Texture* ourTex;
};

