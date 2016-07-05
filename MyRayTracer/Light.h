#pragma once

#include <glm\glm.hpp>

using namespace glm;
using namespace std;

enum LightType { directional, point };

class Light
{
private:


public:
	/*Light(const Light & light)
	{
		type = light.direction;
	}*/
	Light(LightType type, glm::vec3 vec, glm::vec4 _color) : lightType(type), color(_color)
	{
		if (type == directional) // using one or another vector acording to the light type
			direction = vec;
		else
			pos = vec;
	};

	LightType lightType;
	glm::vec3 attenuation = vec3(1.0f, 0.0f,0.0f);
	glm::vec3 pos;
	glm::vec3 direction;
	glm::vec4 color;
	~Light() {};
};