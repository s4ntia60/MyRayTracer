#pragma once
#include "MyObject.h"
#include <glm\glm.hpp>

using namespace glm;

// A mesh is just a set of triplets of vertice's index resulting in a triangle
// vertices are stored in the general scene.
class MyTriangle : public MyObject
{
private:



public:
	vec3 vertices;
	vec4 A;
	vec4 B;
	vec4 C;
	vec4 Atransformed;
	vec4 Btransformed;
	vec4 Ctransformed;

	MyTriangle(vec3 verts, vec4 A, vec4 B, vec4 C) : vertices(verts), A(A), B(B), C(C)
	{ 
		type = triangle; 
	};

	
	~MyTriangle() {};

	bool Intersection(const Ray &ray, HitInfo &output) override;
	bool MollerTrumboreIntersection(const vec3 V1, const vec3 V2, const vec3 V3, Ray ray, HitInfo &output);
	virtual void PreCalc() override;

	/*void AddTriFace(glm::vec3 verticesIndex)
	{
	tri.push_back(verticesIndex);
	}

	void AddTriFaceNormals(glm::vec3 verticesNormalIndex)
	{
	triNormal.push_back(verticesNormalIndex);
	}	*/

};
