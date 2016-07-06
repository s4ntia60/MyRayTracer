#pragma once
#include <vector>
#define GLM_PRECISION_HIGHP_FLOAT
#define GLM_PRECISION_HIGHP_DOUBLE
#include <glm\glm.hpp>



class Ray
{
	
	public:
		glm::vec3 O;
		glm::vec3 D;
		float t;
		Ray(glm::vec3 O, glm::vec3 D, float t);
		~Ray();
};

