#pragma once
#define GLM_PRECISION_HIGHP_FLOAT
#define GLM_PRECISION_HIGHP_DOUBLE
#include <glm/glm.hpp>
// #include <free_image/FreeImage.h>
using namespace glm;

class MyImage
{
public:
	MyImage(int width, int height);
	~MyImage();
	int width;
	int height;
	vec3 **image = nullptr;
	// BYTE * ConvertToOneRowArray();

};

