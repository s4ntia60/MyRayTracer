#include "Ray.h"



Ray::Ray(glm::vec3 P0, glm::vec3 P1, float t )
{
	this->O = P0;
	this->D = P1;
	this->t = t;
}


Ray::~Ray()
{
}
