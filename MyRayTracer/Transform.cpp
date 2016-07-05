// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
	// implementation of Rodrigues equations for arbitrary axis rotation
	vec3 a = glm::normalize(axis);
	mat3 aat = mat3(a.x*a.x, a.x*a.y, a.x*a.z,
		a.x*a.y, a.y*a.y, a.y*a.z,
		a.x*a.z, a.y*a.z, a.z*a.z);

	mat3 aStar = mat3(0, a.z, -a.y,
		-a.z, 0, a.x,
		a.y, -a.x, 0);

	mat3 R = cos(glm::radians(degrees)) * mat3(1);

	R += (1 - cos(glm::radians(degrees))) * aat;

	R += sin(glm::radians(degrees))* aStar;

	return R;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
	mat3 R = Transform::rotate(degrees, up);
	eye = R*eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
	// rotate up is rotate over the c = eye X up axis
	glm::vec3 axis = glm::cross(eye, up);
	axis = glm::normalize(axis);
	up = Transform::rotate(degrees, axis) * up;
	eye = Transform::rotate(degrees, axis) * eye;
}


mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
	vec3 a, b;
	vec3 u, v, w, e;
	a = eye - center; // eye - center
	b = up;

	
	w = glm::normalize(-a);
	u = glm::normalize(glm::cross(b, w));
	v = glm::cross(w, u);
	e = eye;

	// Transform (translate-rotate) matrix
	glm::mat4 m1 = mat4(
		u.x, v.x, w.x, 0,
		u.y, v.y, w.y, 0,
		u.z, v.z, w.z, 0,
		-u.x*e.x - u.y*e.y - u.z*e.z,
		-v.x*e.x - v.y*e.y - v.z*e.z,
		-w.x*e.x - w.y*e.y - w.z*e.z,
		1);

	return m1;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	float n = zNear;
	float f = zFar;
	float theta = fovy / 2;
	theta = glm::radians(theta);
	float d = glm::cos(theta) / glm::sin(theta);
	float A = -((f + n) / (f - n));
	float B = -((2 * f*n) / (f - n));

	/*mat4 ret = mat4(d/aspect, 0,0,0,
	0, d, 0, 0,
	0, 0, A, -1,
	0, 0, B, 0);*/
	mat4 ret = mat4(d / aspect, 0, 0, 0,
		0, d, 0, 0,
		0, 0, A, B,
		0, 0, -1, 0);
	ret = glm::transpose(ret);
	// ret = glm::perspective(fovy, aspect, zNear, zFar);
	//ret = mat4();
	return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
	mat4 ret = mat4(sx, 0, 0, 0,
					0, sy, 0, 0,
					0, 0, sz, 0,
					0, 0, 0, 1);

	return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
	mat4 ret = mat4(1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					tx, ty, tz, 1);

	
	return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
	vec3 x = glm::cross(up,zvec); 
	vec3 y = glm::cross(zvec,x); 
	vec3 ret = glm::normalize(y); 
	return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
