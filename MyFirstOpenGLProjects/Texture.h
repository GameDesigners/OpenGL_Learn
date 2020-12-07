#pragma once
#ifndef Texture_H

#include<iostream>
#include<glad/glad.h>

#include "stb_image.h"

class Texture
{
public:
	unsigned int ID;    //TextureµÄID

	Texture(const std::string& Path);
	void Use();
	void Delete();
};

#endif // !Texture_H



