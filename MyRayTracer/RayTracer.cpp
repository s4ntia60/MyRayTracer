#include "RayTracer.h"
#include <iostream>
#include <math.h>
#include <float.h>
#include <limits>
#include "Transform.h"
#include "RenderSettings.h"
#define EPSILON 0.000001f
#define EPSILON_ADDED 0.001f
bool isDebbuging = false;


void PrintVector(char * name, vec3 vec)
{
	cout << name << " x=" << vec.x << " y=" << vec.y << " z=" << vec.z << endl;
}
RayTracer::RayTracer()
{

}


RayTracer::~RayTracer()
{
}


MyImage RayTracer::RayTrace(Camera *cam, const Scene *scene, int width, int height)
{
	MyImage image(width, height);
	
	if (!&cam || !&scene)
		return image;

	

	for(int j =0; j < height; j++ ) // along vertical
		for (int i = 0; i < width; i++) // along horizontal
		{
			/*if (i > 292 && j > 270)
				isDebbuging = true;*/
				
			float Xmid = (float)i + 0.5f;
			float Ymid = (float)j + 0.5f;
			//PrintStats(i, j, cam->width, cam->height);
			Ray ray =  cam->RayThruPixel(Xmid, Ymid);
			//Ray ray =  cam->RayThruPixel2(Xmid, Ymid);
			
			//Ray ray = cam->eyeRay(Xmid, Ymid, width, height);
			HitInfo hit = Intersect(ray, scene);
			//vec3 color = vec3(FindColor(hit, scene));
			vec3 color = vec3(RecursiveCall(RENDERSETTINGS->tracerDepth, hit, scene));
			image.image[j][i] = clamp(color, 0.0f, 1.0f) * 255.0f;

			if(i == 0)
				cout << "Progress " << ((float)j/(float)height)*100.f << "%" << endl;
		}

	return image;
}




// Get the closest intersection
HitInfo RayTracer::Intersect(Ray ray, const Scene * scene)
{
	float tmin = FLT_MAX;
	HitInfo closestIntersection = HitInfo(vec3(), vec3(), FLT_MAX);
	closestIntersection.hasInstersected = false;

	std::vector<MySphere*>::const_iterator it1;
	std::vector<MyTriangle*>::const_iterator it2;

	for (it2 = scene->triangles.begin(); it2 != scene->triangles.end(); ++it2)
	{
		HitInfo test;
		if ((*it2)->Intersection(ray, test))
		{
			if (test.tValue < tmin && test.tValue > 0)
			{
				tmin = test.tValue;
				closestIntersection = test;				
				closestIntersection.ray = ray;
			}		
		}
	}

	for (it1 = scene->spheres.begin(); it1 != scene->spheres.end(); ++it1)
	{
		HitInfo test;
		if ( (*it1)->Intersection(ray, test))
		{
			if (test.tValue < tmin && test.tValue > 0)
			{
				tmin = test.tValue;
				closestIntersection = test;
				closestIntersection.ray = ray;
			}
		}
	}

	return closestIntersection;
}



vec4 RayTracer::RecursiveCall(int depth, HitInfo hit, const Scene *scene)
{
	if (depth == 0)
	{
		return vec4();
	}else
	if (hit.hasInstersected)
	{
		//vec4 lambert = vec4(0.0f);

		vec4 total = vec4(0.0f);
		vec4 Ir = vec4(0.0f);
		bool isInDarkness;

		total = LightPoint(hit, scene, isInDarkness);
			
		// Recursive Call
		// Get reflected direction ray
		/*vec3 reflectedDir = normalize(glm::reflect(hit.ray.D, vec3(hit.N)));
		vec3 P = hit.P + (reflectedDir  * (EPSILON_ADDED));
		vec3 D = reflectedDir;
		Ray rayReflected = Ray(P, D, 0.0f);
		HitInfo hitReflectedRay = Intersect(rayReflected, scene);
		Ir = RecursiveCall(depth - 1, hitReflectedRay, scene);*/

		// Sum all values
		total = total + hit.material.Ka + hit.material.emission + (Ir * hit.material.Ks);
		return total;


	}
	else
		return vec4(0.0f);
}

vec4 RayTracer::FindColor(HitInfo hit, const Scene *scene)
{
	if (hit.hasInstersected)
	{
		//vec4 lambert = vec4(0.0f);

		vec4 total = vec4(0.0f);
		vec4 Ir = vec4();
		bool isInDarkness;

		total = LightPoint(hit, scene, isInDarkness);
		/*if (!isInDarkness)
			Ir = GetReflectColor(RENDERSETTINGS->tracerDepth, hit, scene);*/

		total = total + hit.material.Ka + hit.material.emission + (Ir * hit.material.Ks);
		//CorrectColor(total);
		return total * 255.0f;
	}		
	else
		return vec4(0.0f);
}

vec4 RayTracer::GetReflectColor(int depth, HitInfo hit, const Scene * scene)
{
	
	
	// Base case
	if (depth == 0)
	{
		return vec4();
	}
	else
	{
		vec3 reflectedDir = normalize(glm::reflect(hit.ray.D, vec3(hit.N)));
		vec3 P = hit.P + (reflectedDir  * (EPSILON_ADDED));
		vec3 D = reflectedDir;
		Ray ray = Ray(P, D, 0.0f);
		
		HitInfo hitNew = Intersect(ray, scene);

		if (hitNew.hasInstersected)
		{
			bool isInDarkness;
			vec4 total = LightPoint(hitNew, scene, isInDarkness);
			vec4 Ir = vec4();
			
			total = LightPoint(hitNew, scene, isInDarkness);
			
			if (!isInDarkness)
				Ir = GetReflectColor(depth-1, hitNew, scene);

			return total + hitNew.material.Ka + hitNew.material.emission + (Ir * hitNew.material.Ks);
			
			
		}
		else
		{
			return vec4(); // end recursivity
			
		}
	}
		
}

float CalcAttenuation(const Light *l, float dist)
{
	if(l->lightType == point)
		return		1.0f / 
			(l->attenuation.x + (l->attenuation.y *dist) + (l->attenuation.z * dist * dist));
	else 
		return 1.0f;
}

vec4 RayTracer::LightPoint(HitInfo hit, const Scene *scene, bool &isInDarkness)
{
	vec4 total = vec4(0.0f);
	isInDarkness = true;
	vector<Light*>::const_iterator it;
	for (it = scene->lights.begin(); it != scene->lights.end(); ++it)
	{
		if (!IsLightBlocked((*it)->pos, hit.P, scene))
		{
			total = (total + ComputeLight(hit, scene, (*it)));

			// apply attenuation
			float dist = length(hit.P - (*it)->pos);
			total = total * CalcAttenuation((*it), dist);

			// is at least visible for one light
			isInDarkness = false;
		}
		else
			total = vec4(1.0f, 0.0f, 0.0f, 0.0f);
				
	}

	
	return total;

}

vec4 RayTracer::ComputeLight(HitInfo hit, const Scene *scene, const Light * light)
{
	vec3 direction;

	if (light->lightType == point)
		direction = normalize(light->pos - hit.P);
	else
	{
		direction = -normalize(light->direction);
	}

	float nDotL = dot(hit.N, direction);
	vec4 lambert = hit.material.Kd * light->color * max(nDotL, 0.0f);

	vec3 eyedirn = normalize(scene->camPos - hit.P);
	vec3 halfvec = normalize(direction + eyedirn);

	float nDotH = dot(hit.N, halfvec);
	vec4 phong = hit.material.Ks * light->color * pow(max(nDotH, 0.0f), hit.material.shininess);
	return phong + lambert;

}

//vec3 RayTracer::ShadingModel(vec3 direction, vec3 eyepos, vec3 lightcolor, vec3 normal, vec3 halfvec, MyMaterial mat)
//{
//	float nDotL = dot(normal, direction);
//	vec3 lambert = vec3(mat.Kd) * lightcolor * max(nDotL, 0.0f);
//
//	
//
//	float nDotH = dot(normal, halfvec);
//	vec3 phong = vec3(mat.Ks) * lightcolor * pow(max(nDotH, 0.0f), mat.shininess);
//	
//
//	return lambert + phong;
//}

bool RayTracer::IsLightBlocked(vec3 lightPos, vec3 point, const Scene * scene)
{
	// Calc the ray components
	vec3 dirToLight = lightPos - point;	
	double a, b, c;	
	double tmin = glm::length(dirToLight);

	dirToLight = normalize(dirToLight);
	point = point + (dirToLight * (EPSILON_ADDED));
	
	
	// Create the ray 
	Ray rayToLight = Ray(point, normalize(dirToLight), tmin);
	
	HitInfo closestIntersection = HitInfo(vec3(), vec3(), FLT_MAX);

	std::vector<MySphere*>::const_iterator it1;
	std::vector<MyTriangle*>::const_iterator it2;
	
	// iterate scene objects and check if there is any intersection with less distance
	for (it2 = scene->triangles.begin(); it2 != scene->triangles.end(); ++it2)
	{
		HitInfo test;
		if ((*it2)->Intersection(rayToLight, test))
			if (test.tValue < tmin && test.tValue > 0)
				return true;
	}

	for (it1 = scene->spheres.begin(); it1 != scene->spheres.end(); ++it1)
	{
		HitInfo test;
		if ((*it1)->Intersection(rayToLight, test))
			if (test.tValue < tmin && test.tValue > 0)
				return true;
				
	}

	return false;
}