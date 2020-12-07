#include "Texture.h"

/// <summary>
/// 创建一个贴图对象
/// </summary>
/// <param name="Path">贴图的路径</param>
Texture::Texture(const std::string& Path)
{
	glGenTextures(1,&ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	//为当前绑定的纹理对象设置环绕[重复]、过滤方式[线性插值]
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//加载并生成纹理
	int width, height, nrChannels;
	unsigned char* data = stbi_load(Path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Fail to load texture from path:\"" << Path << "\"" << std::endl;
	}
	stbi_image_free(data);
}

void Texture::Use()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Delete()
{
	//glDeleteTextures(1,&ID);
}