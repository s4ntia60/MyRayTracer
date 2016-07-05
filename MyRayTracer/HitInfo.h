#pragma once
#include <glm\glm.hpp>
#include "MyMaterial.h"
#include "Ray.h"
using namespace glm;

class HitInfo
{

public:
	bool hasInstersected = false;
	float tValue;
	vec3 P;
	vec3 N;	
	MyMaterial material;
	Ray ray = Ray(vec3(), vec3(), 0.0f);
	
	HitInfo() {};
	HitInfo(vec3 intecPoint, vec3 normal, float tValue);
	~HitInfo();
};

