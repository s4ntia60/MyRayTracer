#pragma once
#include "MyObject.h"


class MySphere : public MyObject
{
public:
	float x;
	float y;
	float z;
	float radius;
	MySphere(float x, float y, float z, float radius) : x(x), y(y), z(z), radius(radius)
	{
		type = sphere;
	}
	~MySphere()
	{

	};
	virtual void PreCalc() override;
	bool Intersection(const Ray &ray, HitInfo &output) override;
};