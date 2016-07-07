#include "MySphere.h"
#include <iostream>
#define GLM_PRECISION_HIGHP_FLOAT
#define GLM_PRECISION_HIGHP_DOUBLE
#include <glm\glm.hpp>
using namespace glm;

void MySphere::PreCalc()
{
	inverseTransform = glm::inverse(transform);
	inverseTransposeTransform = glm::transpose(inverseTransform);
	inverseTransposeTransform3x3 = mat3(inverseTransposeTransform);

}



bool MySphere::Intersection(const Ray & ray, HitInfo & output)
{
	const vec3 oldP0 = ray.O;
	const vec3 oldP1 = ray.D;

	const mat4 inverse = inverseTransform;
	
	// apply inverse transform to the ray
	vec3 O = vec3(inverse * vec4(ray.O, 1.0));				// 1 -> point
	vec3 D = normalize(vec3(inverse * vec4(ray.D, 0.0)));	// 0 -> vector

	//A = Xd^2 + Yd^2 + Zd^2 = 1 since |P1| 
	const double A = pow(D.x, 2.0) + pow(D.y, 2.0) + pow(D.z, 2.0);
	

	// B = 2 * (Xd * (X0 - Xc) + Yd * (Y0 - Yc) + Zd * (Z0 - Zc))
	const double B = 2.0f * (D.x * (O.x - x) +
		(D.y * (O.y - y)) +
		(D.z * (O.z - z)));

	// C = (X0 - Xc) ^ 2 + (Y0 - Yc) ^ 2 + (Z0 - Zc) ^ 2 - Sr ^ 2
	const double C = pow((O.x - x), 2.0) +
		pow((O.y - y), 2.0) +
		pow((O.z - z), 2.0) -
		pow(radius, 2.0);

	const double discriminant = (B * B) - (4.0 *A* C);


	if (discriminant < 0.0) // No intersection
	{
		return false;
	}
	else if (discriminant >= 0.0)
	{
		const double sqrtDiscriminant = sqrt(discriminant);
		
		// calc t0 and check if it is valid
		double t0 = (-B - sqrtDiscriminant) / (2.0f * A);
		double t1 = (-B + sqrtDiscriminant) / (2.0f * A);

		/*if (t0 > 0.0f && t1 < 0.0f)
			std::cout << "Punto interior" << endl;
		if (t1 > 0.0f && t0 < 0.0f)
			std::cout << "Punto interior" << endl;*/

		
		double tValue = 0;

		// t0 is valid
		if (t0 > 0.0)
		{
			tValue = t0;
		}
		else 
		{
			
			// then it is t1
			t1 = (-B + sqrtDiscriminant) / (2.0f * A);
			tValue = t1;
			
			if (t1 <= 0.0)
				return false;
			
		}

		// compute intersection
		// take intersection point back to the actual object's transform
		vec4 intersectionP = vec4((O + D * (float)tValue), 1.0);				
		vec4 intersectionObjSpace = transform * intersectionP;
		
		// Calc normal
		vec4 normal = normalize(intersectionP - vec4(x, y, z, 0.0f));
		vec3 normalTransformed = normalize(inverseTransposeTransform3x3 * vec3(normal));

		// Calc depth value
		float t = glm::length(vec3(intersectionObjSpace) - oldP0);		
		
		// Set output
		output = HitInfo(vec3(intersectionObjSpace), vec3(normalTransformed), t);
		output.hasInstersected = true;
		output.material = material;

		return true;

	}

	return false;

}


