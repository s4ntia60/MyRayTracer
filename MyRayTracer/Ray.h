#pragma once
#include <vector>
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

