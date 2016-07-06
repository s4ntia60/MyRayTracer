#pragma once
#include <stack>
#define GLM_PRECISION_HIGHP_FLOAT
#define GLM_PRECISION_HIGHP_DOUBLE
#include <glm\glm.hpp>
// Readfile definitions 
class Scene;
class Camera;


void matransform (std::stack<glm::mat4> &transfstack, float * values) ;
void rightmultiply (const glm::mat4 & M,  std::stack<glm::mat4> &transfstack) ;
bool readvals (stringstream &s, const int numvals, float * values) ;
void readfile (const char * filename, Camera * cam, Scene * scene);
