#include "MyTriangle.h"
#define GLM_PRECISION_HIGHP_FLOAT
#define GLM_PRECISION_HIGHP_DOUBLE
#include <glm\glm.hpp>
using namespace glm;

#define EPSILON 0.000001

bool MyTriangle::MollerTrumboreIntersection(const vec3 V1, const vec3 V2, const vec3 V3, Ray ray, HitInfo &output)
{
	output = HitInfo(vec3(), vec3(), 0);
	output.hasInstersected = false;
	vec3 e1, e2;  //Edge1, Edge2
	vec3 P, Q, T;
	float det, inv_det, u, v;
	float t;
	ray.D = glm::normalize(ray.D);
	//Find vectors for two edges sharing V1
	e1 = V2 - V1;
	e2 = V3 - V1;
	//Begin calculating determinant - also used to calculate u parameter
	P = glm::cross(ray.D, e2);
	//if determinant is near zero, ray lies in plane of triangle
	det = glm::dot(e1, P);
	//NOT CULLING
	if (det > -EPSILON && det < EPSILON) return false;
	inv_det = 1.f / det;

	//calculate distance from V1 to ray origin
	T = ray.O - V1;

	//Calculate u parameter and test bound
	u = dot(T, P) * inv_det;
	//The intersection lies outside of the triangle
	if (u < 0.f || u > 1.f) return false;

	//Prepare to test v parameter
	Q = cross(T, e1);

	//Calculate V parameter and test bound
	v = dot(ray.D, Q) * inv_det;
	//The intersection lies outside of the triangle
	if (v < 0.f || u + v  > 1.f) return false;

	t = dot(e2, Q) * inv_det;

	if (t > EPSILON)
	{
		//ray intersection
		
		output.hasInstersected = true;
		output.tValue = t;
		output.P = ray.O + output.tValue * ray.D;
		output.N = normalize(glm::cross(V2 - V1, V3 - V1));
		output.material = material;
		return true;
	}

	// No hit, no win
	output.hasInstersected = false;
	return false;
}
bool MyTriangle::Intersection(const Ray &ray, HitInfo &output)
{
	output = HitInfo(vec3(), vec3(), FLT_MAX);
	
	vec3 A = vec3(Atransformed);
	vec3 B = vec3(Btransformed);
	vec3 C = vec3(Ctransformed);

	//return MollerTrumboreIntersection(A, B, C, ray, output);
	
	output.hasInstersected = true;
	float tMin = 0;
	float tMax = FLT_MAX;
	

	vec3 vAB = B - A;
	vec3 vAC = C - A;
	vec3 norm = normalize(cross(vAB, vAC));

	// Triangle plane intersection distance
	output.tValue = dot(norm, A - ray.O) / dot(norm, ray.D);

	vec3 q = ray.O + output.tValue * ray.D; // hit point

											// Compute barycentric coordinates
	vec3 vAQ = q - A;

	float dAB_AB = dot(vAB, vAB);
	float dAB_AC = dot(vAB, vAC);
	float dAC_AC = dot(vAC, vAC);
	float dAQ_AB = dot(vAQ, vAB);
	float dAQ_AC = dot(vAQ, vAC);

	float D = dAB_AB * dAC_AC - dAB_AC * dAB_AC; // determinant

	if (D == 0.0f)
	{
		output.hasInstersected = false; // ray parallel to triangle plane
		return false;
	}

	float beta = (dAC_AC * dAQ_AB - dAB_AC * dAQ_AC) / D;
	float gamma = (dAB_AB * dAQ_AC - dAB_AC * dAQ_AB) / D;
	
	// If it misses, return false
	if (beta < 0.0f || gamma < 0.0f) output.hasInstersected = false;
	if (beta > 1.0f || gamma > 1.0f) output.hasInstersected = false;
	if (beta + gamma > 1.0f) output.hasInstersected = false;
	if (output.tValue < tMin || output.tValue > tMax) output.hasInstersected = false;

	if (!output.hasInstersected)
		return false;


	output.hasInstersected = true;
	// It's a hit, so update result and return true
	output.P = q;
	output.material = material;
	output.N = norm;
	// interpolate normal
	float alpha = 1.0f - beta - gamma;


	return true;	
}

void MyTriangle::PreCalc()
{
	inverseTransform = glm::inverse(transform);
	inverseTransposeTransform = glm::transpose(inverseTransform);

	Atransformed = transform * A;
	Btransformed = transform * B;
	Ctransformed = transform * C;
}
