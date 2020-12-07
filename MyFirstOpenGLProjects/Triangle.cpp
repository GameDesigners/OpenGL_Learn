#include "Triangle.h"

Triangle::Triangle(string _vetexFilePath,string _fragmentFilePath)
{
    ourShader = new Shader(_vetexFilePath.c_str(), _fragmentFilePath.c_str());
    PrepareData();
}

Triangle::Triangle(string _vetexFilePath, string _fragmentFilePath,GLenum _rendermode)
{

    ourShader = new Shader(_vetexFilePath.c_str(), _fragmentFilePath.c_str());
    renderMode = _rendermode;
    PrepareData();
}

/// <summary>
/// ׼������
/// </summary>
void Triangle::PrepareData()
{

#pragma region ����������
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //ר�����ö����ʽ�ģ������ϵ����ݶ�Ӧʲô���ԣ�
    //0Ϊλ������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //1Ϊ��ɫ����
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));  //�ӵ�����������ʼ
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
#pragma endregion
}

/// <summary>
/// ʵʱ��Ⱦ
/// </summary>
void Triangle::Rendering()
{
    ourShader->Use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

/// <summary>
/// �������
/// </summary>
void Triangle::DeleteData()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    ourShader->Delete();
}