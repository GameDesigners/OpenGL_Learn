#include "Edge.h"

Edge::Edge(string _vetexFilePath, string _fragmentFilePath, string _texturePath)
{
    ourShader = new Shader(_vetexFilePath.c_str(), _fragmentFilePath.c_str());
    ourTex = new Texture(_texturePath);
    PrepareData();
}

Edge::Edge(string _vetexFilePath, string _fragmentFilePath,GLenum _rendermode, string _texturePath)
{
    ourShader = new Shader(_vetexFilePath.c_str(), _fragmentFilePath.c_str());
    ourTex = new Texture(_texturePath);
    renderMode = _rendermode; 
    PrepareData();
}

/// <summary>
/// 渲染过程
/// </summary>
void Edge::PrepareData()
{
#pragma region 处理顶点数据
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (renderMode == GL_LINE)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#pragma endregion
}

void Edge::Rendering()
{
    ourShader->Use();
    glActiveTexture(GL_TEXTURE0);
    ourTex->Use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);
}

void Edge::DeleteData()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    ourShader->Delete();
    ourTex->Delete();
    delete ourShader;
    delete ourTex;
}