#include "Scene.h"
using namespace glm;


Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::AddSphere(MySphere * sphere)
{
	if (sphere)
	{
		spheres.push_back(sphere);
		objectsNumber++;
	}
}

void Scene::AddTriangle(MyTriangle * triangle)
{
	if (triangle)
	{
		triangles.push_back(triangle);
		objectsNumber++;
	}
		
}

void Scene::AddLight(Light * light)
{
	if (light)
		lights.push_back(light);

}


void Scene::SetMaxVerts(int maxVerts)
{
	this->maxVerts = maxVerts;
	if (maxVerts > 0)
		vertices = new glm::vec3[maxVerts];
}

void Scene::SetMaxVertNormal(int maxVertexNormals)
{
	maxVertNorms = maxVertexNormals;
	if (maxVertNorms > 0)
		vertexNormals = new vec6[maxVertNorms];
}

void Scene::AddVertex(glm::vec3 vec)
{
	if (vertCounter < maxVerts)
		vertices[vertCounter] = vec;

	vertCounter++;
}

void Scene::AddVertexNormal(vec6 vec)
{
	if (vertNormalCounter < maxVertNorms)
		vertexNormals[vertNormalCounter] = vec;

	vertNormalCounter++;
}
