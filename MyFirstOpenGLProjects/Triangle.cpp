#include "Triangle.h"

Triangle::Triangle()
{
    SetVertexShader();
    SetPixelShader();
}

Triangle::Triangle(GLenum _rendermode)
{
    SetVertexShader();
    SetPixelShader();
    renderMode = _rendermode;
}


void Triangle::SetVertexShader()
{
   vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
}

void Triangle::SetPixelShader()
{
    
    pixelShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
}

/// <summary>
/// ׼������
/// </summary>
void Triangle::PrepareData()
{
#pragma region ���붥����ɫ��
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);  //����Shader

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderCompileSuc);
    if (!shaderCompileSuc)
    {
        glGetShaderInfoLog(vertexShader, 512,NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
#pragma endregion

#pragma region ����ƬԪ��ɫ��
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

#pragma region  ������ɫ��
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

#pragma region ����������
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
#pragma endregion
}

/// <summary>
/// ʵʱ��Ⱦ
/// </summary>
void Triangle::Rendering()
{
    glUseProgram(shaderProgram);
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
    glDeleteProgram(shaderProgram);
}