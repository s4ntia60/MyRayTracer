#include "HitInfo.h"


HitInfo::HitInfo(vec3 intecPoint, vec3 normal, float tValue)
{
	this->P = intecPoint;
	this->N = normal;
	this->tValue = tValue;
}

HitInfo::~HitInfo()
{
}
