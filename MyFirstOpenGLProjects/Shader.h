#pragma once
#ifndef  SHADER_H

#ifndef __glad_h_
#include <glad\glad.h>
#endif

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

class Shader
{
public:
	unsigned int ID;    //Shader的程序ID
	Shader(const GLchar* vertexPath, const GLchar* fragmengPath);
	void Use();
	void Delete();

	//uniform 工具
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setFloat4f(const std::string& name, float x,float y,float z,float w)
	{
		
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}

private:
	//log变量
	int shaderCompileSuc;     //Shader编译是否成功
	int shaderLinkSuc;        //Shader链接是否成功
	char infoLog[512];        //Log数组
};
#endif // ! SHADER_H
