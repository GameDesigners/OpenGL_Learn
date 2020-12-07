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
    //��������
    float vertices[18] = {
        -0.5f, -0.5f, 0.0f,1.0f,0.0f,0.0f, // left  
         0.5f, -0.5f, 0.0f, 0.0f,1.0f,0.0f,// right 
         0.0f,  0.5f, 0.0f,0.0f,0.0f,1.0f  // top   
    };

    unsigned int VBO = NULL;                  //���㻺�����
    unsigned int VAO = NULL;                  //�����������

    //��Ⱦ����
    GLenum renderMode = GL_FILL;        //��Ⱦģʽ

public:
	Triangle(string _vetexFilePath, string _fragmentFilePath);
    Triangle(string _vetexFilePath, string _fragmentFilePath,GLenum _rendermode);

    void PrepareData();  //׼������
	void Rendering();    //��Ⱦ
    void DeleteData();

private:
    Shader* ourShader;
};

