#include "Camera.h"


using namespace glm;
#define M_PI 3.14159265358979323846


Camera::Camera(glm::vec3 _lookfrom, glm::vec3 _lookat, glm::vec3 _up, float _fovy)
{
	lookfrom = _lookfrom;
	lookat = _lookat;
	up = _up;
	fovY = _fovy;
}

Camera::Camera(){}

void Camera::PreCalc()
{
	// Calc CoordFrame
	vec3 a = (lookfrom - lookat);
	vec3 b = up;
	
	w = glm::normalize(a);
	u = glm::normalize(glm::cross(b, w));
	v = glm::cross(w, u);
	
	halfFovY = fovY / 2.0f;
	double fovyRads = fovY * M_PI / 180.0;
	// Calc verticalFov
	double aspectRatio = (double)width / (double)height;
	//fovX = 2.0f * atan(tan(glm::radians((halfFovY)) * (aspectRatio))); // In Rads
	fovX = 2 * atan(tan(fovyRads / 2) * (aspectRatio));
	// pre cal tan of half fovs
	tanHalfFovX = tan(fovX / 2.0);
	tanHalfFovY = tan(fovyRads/2.0);

	halfHeight = ((double)height) / 2.0;
	halfWidth = ((double)width) / 2.0;
}

Ray Camera::RayThruPixel2(float x, float y)
{
	double fovyRads, fovxRads; //fovy is provided, but fovx has to be calculated
	double alpha, beta; //used to compute ray direction
	double xCenter, yCenter; //auto grader sends rays through the center of a pixel
	//glm::vec3 u, v, w; //orthonormal basis for the camera

	fovyRads = fovY * M_PI / 180;
	fovxRads = 2 * atan(tan(fovyRads / 2) * ((float)width / (float)height));

	xCenter = x;
	yCenter = y;

	//w = glm::normalize(eye - center);
	//u = glm::normalize(glm::cross(up, w));
	//v = glm::cross(w, u);

	//alpha = tan(fovxRads / 2) * ((xCenter - (width / 2)) / (width / 2));
	//beta = tan(fovyRads / 2) * (((height / 2) - yCenter) / (height / 2));

	alpha = tanHalfFovX * ((x - (halfWidth)) / (halfWidth));
	beta = tanHalfFovY * ((halfHeight - y) / (halfHeight));


	glm::vec3 dirn = glm::normalize((u * (float)alpha +(- v * (float)beta) - w));

	return Ray(lookfrom, glm::vec3(dirn.x, dirn.y, dirn.z), 0.0f);
}

Ray Camera::RayThruPixel(float x, float y)
{
	

	float alpha = tanHalfFovX * ((x  - (halfWidth)) / (halfWidth));
	float beta =  tanHalfFovY * ((halfHeight - y ) / (halfHeight));

	vec3 O = lookfrom;
	vec3 D = glm::normalize((alpha*u) + (-beta*v) - w);
	float t = 10000;

	return Ray(O, D, t);
}

Ray Camera::eyeRay(int x, int y, int imageWidth, int imageHeight)
{
	vec3 m_viewDir = lookfrom - lookat;
	// first compute the camera coordinate system 
	// ------------------------------------------

	// wDir = e - (e+m_viewDir) = -m_vView
	/*const vec3 wDir = glm::normalize(vec3(m_viewDir));
	const vec3 uDir = glm::normalize(glm::cross(up, wDir));
	const vec3 vDir = glm::cross(wDir, uDir);*/

	const vec3 wDir = w;
	const vec3 uDir = u;
	const vec3 vDir = v;

	// next find the corners of the image plane in camera space
	// --------------------------------------------------------

	const float aspectRatio = (float)imageWidth / (float)imageHeight;


	const float top = tan(radians(fovY / 2.0f));
	const float right = aspectRatio*top;

	const float bottom = -top;
	const float left = -right;



	// transform x and y into camera space 
	// -----------------------------------

	const float imPlaneUPos = left + (right - left)*(((float)x) / (float)imageWidth);
	const float imPlaneVPos = bottom + (top - bottom)*(((float)y) / (float)imageHeight);

	return Ray(lookfrom, glm::normalize(imPlaneUPos*uDir + imPlaneVPos*vDir - wDir), 99999);
}


Camera::~Camera()
{
}
