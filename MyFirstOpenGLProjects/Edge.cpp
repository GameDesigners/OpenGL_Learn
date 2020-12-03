#include "Edge.h"

Edge::Edge()
{
    SetVertexShader();
    SetPixelShader();
}

Edge::Edge(GLenum _rendermode)
{
    SetVertexShader();
    SetPixelShader();
    renderMode = _rendermode;
}

void Edge::SetVertexShader()
{
    vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
}

void Edge::SetPixelShader()
{

    pixelShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
}

/// <summary>
/// 渲染过程
/// </summary>
void Edge::PrepareData()
{
#pragma region 编译顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);  //编译Shader

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderCompileSuc);
    if (!shaderCompileSuc)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
#pragma endregion

#pragma region 编译片元着色器
    unsigned int pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(pixelShader, 1, &pixelShaderSource, NULL);
    glCompileShader(pixelShader);

    glGetShaderiv(pixelShader, GL_COMPILE_STATUS, &shaderLinkSuc);
    if (!shaderCompileSuc)
    {
        glGetShaderInfoLog(pixelShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
#pragma endregion

#pragma region  链接着色器
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, pixelShader);
    glLinkProgram(shaderProgram);

    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &shaderLinkSuc);
    if (!shaderLinkSuc)
    {
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(pixelShader);
#pragma endregion

#pragma region 处理顶点数据
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    if (renderMode == GL_LINE)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#pragma endregion
}

void Edge::Rendering()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Edge::DeleteData()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
}