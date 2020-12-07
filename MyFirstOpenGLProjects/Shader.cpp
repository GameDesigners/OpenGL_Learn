#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmengPath)
{
	//从文件路径中获取顶点、片段着色器
	std::string vertexCode;        
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	//保证ifstream对象可以抛出异常
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//打开文件
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmengPath);

		std::stringstream vShaderStream, fShaderStream;
		//读取文件的缓冲数据到数据流
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//关闭文件处理器
		vShaderFile.close();
		fShaderFile.close();

		//转换数据到string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

#pragma region 编译顶点着色器
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
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
	glShaderSource(pixelShader, 1, &fShaderCode, NULL);
	glCompileShader(pixelShader);

	glGetShaderiv(pixelShader, GL_COMPILE_STATUS, &shaderCompileSuc);
	if (!shaderCompileSuc)
	{
		glGetShaderInfoLog(pixelShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
#pragma endregion

#pragma region  链接着色器
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
