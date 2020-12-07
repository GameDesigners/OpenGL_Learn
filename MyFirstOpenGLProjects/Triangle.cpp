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
/// 准备数据
/// </summary>
void Triangle::PrepareData()
{

#pragma region 处理顶点数据
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //专门设置顶点格式的（顶点上的数据对应什么属性）
    //0为位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //1为颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));  //从第三个变量开始
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
#pragma endregion
}

/// <summary>
/// 实时渲染
/// </summary>
void Triangle::Rendering()
{
    ourShader->Use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

/// <summary>
/// 清除数据
/// </summary>
void Triangle::DeleteData()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    ourShader->Delete();
}