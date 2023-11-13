#pragma once
#include "MyImage.h"
#include "Scene.h"
#include "Camera.h"
#include "Ray.h"
#include "HitInfo.h"
#define GLM_PRECISION_HIGHP_FLOAT
#define GLM_PRECISION_HIGHP_DOUBLE
#include <glm/glm.hpp>
class RayTracer
{
private: 
	Camera * actualCam;
public:
	RayTracer();
	~RayTracer();

	MyImage RayTrace(Camera *cam, const Scene *scene, int width, int height);
	HitInfo Intersect(Ray ray, const Scene * scene);
	//vec4 FindColor(HitInfo hit, const Scene * scene);
	bool IsLightBlocked(vec3 lightPos, vec3 point, const Scene * scene);
	//vec4 GetReflectColor(int depth, HitInfo hit, const Scene * scene);
	//vec3 ShadingModel(vec3 direction, vec3 eyepos, vec3 lightcolor, vec3 normal, vec3 halfvec, MyMaterial mat);
	vec4 LightPoint(HitInfo hit, const Scene *scene, bool & isInDarkness);
	vec4 ComputeLight(HitInfo hit, const Scene *scene, const Light * light);
	vec4 RecursiveCall(int depth, HitInfo hit, const Scene *scene);
	vec4 Radiance(Ray &ray, int depth, const Scene * scene);
	//HitInfo TestSphereIntersection(Ray ray, MySphere sphere);
	//HitInfo TestMeshIntersection(Ray ray, MyTriangle tri, Scene * scene, Camera * cam);
	
};

