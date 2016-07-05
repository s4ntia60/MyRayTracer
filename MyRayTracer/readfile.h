#pragma once
#include <stack>
#include <glm\glm.hpp>
// Readfile definitions 
class Scene;
class Camera;


void matransform (std::stack<glm::mat4> &transfstack, float * values) ;
void rightmultiply (const glm::mat4 & M,  std::stack<glm::mat4> &transfstack) ;
bool readvals (stringstream &s, const int numvals, float * values) ;
void readfile (const char * filename, Camera * cam, Scene * scene);
