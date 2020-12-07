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
    //��������
    float vertices[32] =
    {
    //  -----λ��--------   -----��ɫ------  -��������-
        0.5f,  0.5f, 0.0f,  1.0f,0.0f,0.0f,  1.0f,1.0f,            // ���Ͻ�
        0.5f, -0.5f, 0.0f,  0.0f,1.0f,0.0f,  1.0f,0.0f,           // ���½�
       -0.5f, -0.5f, 0.0f,  0.0f,0.0f,1.0f,  0.0f,0.0f,           // ���½�
       -0.5f,  0.5f, 0.0f,  1.0f,1.0f,0.0f,  0.0f,1.0f           // ���Ͻ�
    };

    //��������
    unsigned int indices[6] =
    { 
        // ע��������0��ʼ! 
        0, 1, 3, // ��һ��������
        1, 2, 3  // �ڶ���������
    };

    unsigned int VBO;                  //���㻺�����
    unsigned int VAO;                  //�����������
    unsigned int EBO;                  //�����������

    //��Ⱦ����
    GLenum renderMode= GL_FILL;        //��Ⱦģʽ


public:
    Edge(string _vetexFilePath, string _fragmentFilePath, string _texturePath);
    Edge(string _vetexFilePath, string _fragmentFilePath,GLenum _rendermode, string _texturePath);


    void PrepareData();  //׼������
    void Rendering();    //��Ⱦ
    void DeleteData();

private:
    Shader* ourShader;
    Texture* ourTex;
};

