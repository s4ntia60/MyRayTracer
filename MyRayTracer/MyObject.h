#pragma once

#include <vector>
#define GLM_PRECISION_HIGHP_FLOAT
#define GLM_PRECISION_HIGHP_DOUBLE
#include <glm/glm.hpp>
#include "Ray.h"
#include "HitInfo.h"
#include "MyMaterial.h"
using namespace glm;
using namespace std;

enum ObjectType { sphere, triangle, light };

class MyObject
{
public:
	ObjectType type;
	float size;
	MyMaterial material;
	mat4 transform;
	mat4 inverseTransform;
	mat4 inverseTransposeTransform;
	mat3 inverseTransposeTransform3x3;
	MyObject() {};
	virtual ~MyObject() {};
	virtual bool Intersection(const Ray &ray, HitInfo &output) = 0;
	virtual void PreCalc() = 0;
};

