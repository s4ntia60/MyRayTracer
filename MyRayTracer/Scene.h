#pragma once
#include <vector>
#define GLM_PRECISION_HIGHP_FLOAT
#define GLM_PRECISION_HIGHP_DOUBLE
#include <glm\glm.hpp>
#include "MyTriangle.h"
#include "MySphere.h"
#include "Light.h"
using namespace glm;
using namespace std;

// For storing vertex normals
struct vec6
{
	float d1, d2, d3, d4, d5, d6;
	vec6(float d1, float d2, float d3, float d4, float d5, float d6) :
		d1(d1), d2(d2), d3(d3), d4(d4), d5(d5), d6(d6){}
	vec6() {};
};


class Scene
{

private:

	int vertCounter = 0;
	int vertNormalCounter = 0;
	int maxVerts;
	int maxVertNorms;	
	vec6 * vertexNormals;

	

public:
	vec3 camPos;
	int objectsNumber = 0;
	vector<MySphere*> spheres;
	vector<MyTriangle*> triangles;
	vector<Light*> lights;
	glm::vec3 * vertices;
	Scene();
	~Scene();
	
	void AddSphere(MySphere * sphere);
	void AddTriangle(MyTriangle * triangle);
	void AddLight(Light * light);
	void SetMaxVerts(int maxVerts);
	void SetMaxVertNormal(int maxVertexNormals);
	void AddVertex(glm::vec3 vec);
	void AddVertexNormal(vec6 vec);



};

