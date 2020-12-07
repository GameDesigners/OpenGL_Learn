#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmengPath)
{
	//���ļ�·���л�ȡ���㡢Ƭ����ɫ��
	std::string vertexCode;        
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	//��֤ifstream��������׳��쳣
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//���ļ�
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmengPath);

		std::stringstream vShaderStream, fShaderStream;
		//��ȡ�ļ��Ļ������ݵ�������
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//�ر��ļ�������
		vShaderFile.close();
		fShaderFile.close();

		//ת�����ݵ�string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

#pragma region ���붥����ɫ��
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);  //����Shader

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderCompileSuc);
	if (!shaderCompileSuc)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
#pragma endregion

#pragma region ����ƬԪ��ɫ��
	unsigned int pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(pixelShader, 1, &fShaderCode, NULL);
	glCompileShader(pixelShader);

	glGetShaderiv(pixelShader, GL_COMPILE_STATUS, &shaderCompileSuc);
	if (!shaderCompileSuc)
	{
		glGetShaderInfoLog(pixelShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
#pragma endregion

#pragma region  ������ɫ��
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, pixelShader);
	glLinkProgram(ID);

	glGetShaderiv(ID, GL_LINK_STATUS, &shaderLinkSuc);
	if (!shaderLinkSuc)
	{
		glGetShaderInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(pixelShader);
#pragma endregion
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}
