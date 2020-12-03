#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;

#ifndef __glad_h_
#include <glad\glad.h>
#endif

class Edge
{
public:
    //��������
    float vertices[12] =
    {
        0.5f, 0.5f, 0.0f,   // ���Ͻ�
        0.5f, -0.5f, 0.0f,  // ���½�
        -0.5f, -0.5f, 0.0f, // ���½�
        -0.5f, 0.5f, 0.0f   // ���Ͻ�
    };

    //��������
    unsigned int indices[6] =
    { 
        // ע��������0��ʼ! 
        0, 1, 3, // ��һ��������
        1, 2, 3  // �ڶ���������
    };

    const char* vertexShaderSource;    //������ɫ��
    const char* pixelShaderSource;     //������ɫ��

    int shaderProgram;                 //��ɫ������
    unsigned int VBO;                  //���㻺�����
    unsigned int VAO;                  //�����������
    unsigned int EBO;                  //�����������

    //��Ⱦ����
    GLenum renderMode= GL_FILL;        //��Ⱦģʽ

    //log����
    int shaderCompileSuc;     //Shader�����Ƿ�ɹ�
    int shaderLinkSuc;        //Shader�����Ƿ�ɹ�
    char infoLog[512];        //Log����

public:
    Edge();
    Edge(GLenum _rendermode);

    void SetVertexShader();
    void SetPixelShader();
    void PrepareData();  //׼������
    void Rendering();    //��Ⱦ
    void DeleteData();
};

