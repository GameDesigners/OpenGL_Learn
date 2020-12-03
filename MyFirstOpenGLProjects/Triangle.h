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
    //��������
    float vertices[9] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    };

    const char* vertexShaderSource;    //������ɫ��
    const char* pixelShaderSource;     //������ɫ��

    int shaderProgram;                 //��ɫ������
    unsigned int VBO;                  //���㻺�����
    unsigned int VAO;                  //�����������

    //��Ⱦ����
    GLenum renderMode = GL_FILL;        //��Ⱦģʽ

    //log����
    int shaderCompileSuc;     //Shader�����Ƿ�ɹ�
    int shaderLinkSuc;        //Shader�����Ƿ�ɹ�
    char infoLog[512];        //Log����

public:
	Triangle();
    Triangle(GLenum _rendermode);

    void SetVertexShader();
    void SetPixelShader();
    void PrepareData();  //׼������
	void Rendering();    //��Ⱦ
    void DeleteData();
};

