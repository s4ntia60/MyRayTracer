#pragma once
#include <glm\glm.hpp>
using namespace glm;

class MyMaterial
{
public:

	vec4 Ka = vec4( .2f, .2f, .2f, 0.f );
	vec4 Kd = vec4(0.0f);
	vec4 Ks = vec4(0.0f);
	vec4 emission = vec4(0.0f);
	float shininess = 0;
	
	MyMaterial();
	~MyMaterial();
};

