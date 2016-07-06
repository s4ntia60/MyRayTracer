#pragma once
#define GLM_PRECISION_HIGHP_FLOAT
#define GLM_PRECISION_HIGHP_DOUBLE
#include <glm\glm.hpp>
#include "Ray.h"
using namespace glm;

class Camera
{
private:
	
public:
	int width;
	int height;

	double fovY;  // FOV in Y axis
	double fovX;
	double halfFovY;
	double tanHalfFovX;
	double tanHalfFovY;
	double halfHeight;
	double halfWidth;


	glm::vec3 lookfrom;
	glm::vec3 lookat;
	glm::vec3 up;
	glm::vec3 w;
	glm::vec3 u;
	glm::vec3 v;

	Camera(glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 up, float fov);
	Camera();
	void PreCalc();
	
	Ray RayThruPixel(float x, float y);
	Ray RayThruPixel2(float x, float y);
	Ray eyeRay(int x, int y, int imageWidth, int imageHeight);

	~Camera();
};

