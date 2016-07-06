/*****************************************************************************/
/* This is the program skeleton for homework 2 in CSE167x by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

/*****************************************************************************/
// This file is readfile.cpp.  It includes helper functions for matrix 
// transformations for a stack (matransform) and to rightmultiply the 
// top of a stack.  These functions are given to aid in setting up the 
// transformations properly, and to use glm functions in the right way.  
// Their use is optional in your program.  
  

// The functions readvals and readfile do basic parsing.  You can of course 
// rewrite the parser as you wish, but we think this basic form might be 
// useful to you.  It is a very simple parser.

// Please fill in parts that say YOUR CODE FOR HW 2 HERE. 
// Read the other parts to get a context of what is going on. 
  
/*****************************************************************************/

// Basic includes to get this file to work.  
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#define GLM_PRECISION_HIGHP_FLOAT
#define GLM_PRECISION_HIGHP_DOUBLE
#include <glm\glm.hpp>
#include "Transform.h" 

using namespace std;
//#include "variables.h" 
#include "readfile.h"
#include "Camera.h"
#include "Scene.h"
#include "RenderSettings.h"
#include "MyMaterial.h"

// You may not need to use the following two functions, but it is provided
// here for convenience

// The function below applies the appropriate transform to a 4-vector
void matransform(stack<mat4> &transfstack, float* values) 
{
	mat4 transform = transfstack.top(); 
	vec4 valvec = vec4(values[0],values[1],values[2],values[3]); 
	vec4 newval = transform * valvec; 
	for (int i = 0; i < 4; i++) values[i] = newval[i]; 
}

void rightmultiply(const mat4 & M, stack<mat4> &transfstack) 
{
	mat4 &T = transfstack.top(); 
	T = T * M; 
}

void leftmultiply(const mat4 & inverseM, stack<mat4> &transfInverseStack)
{
	mat4 &T = transfInverseStack.top();
	T = inverseM * T;
}

// Function to read the input data values
// Use is optional, but should be very helpful in parsing.  
bool readvals(stringstream &s, const int numvals, float* values) 
{
	for (int i = 0; i < numvals; i++) {
		s >> values[i]; 
		if (s.fail()) {
			cout << "Failed reading value " << i << " will skip\n"; 
			return false;
		}
	}
	return true;
}

void readfile(const char* filename, Camera * cam, Scene * scene) 
{
	string str, cmd; 
	ifstream in;
	in.open(filename);	
	
	if (in.is_open()) 
	{

		// I need to implement a matrix stack to store transforms.  
		// This is done using standard STL Templates 
		stack <mat4> transfstack; 
		transfstack.push(mat4(1.0));  // identity

		stack <mat4> transfInverseStack;
		transfInverseStack.push(mat4(1.0));  //identity

		MyObject * objectAux = nullptr;
		Light * lightAux = nullptr;
		
		MyMaterial materialAux;
		vec3 attenuationAux = vec3(1.0f, 0.0f, 0.0f);



		getline (in, str); 
		int numused = 0;
		while (in) 
		{

			cout << "\nLine:: " << str << std::endl;
			if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
				// Ruled out comment and blank lines 

				stringstream s(str);
				s >> cmd; 
				float values[10]; // Position and color for light, colors for others
									// Up to 10 params for cameras.  
				bool validinput; // Validity of input 

				if (cmd == "size")
				{
					validinput = readvals(s, 2, values);
					if (validinput)
					{
						cam->width = (int) values[0];  
						cam->height = (int)values[1];
						RENDERSETTINGS->width  = (int)values[0];
						RENDERSETTINGS->height = (int)values[1];

					}
				}
				else
				if (cmd == "maxdepth")
				{
					validinput = readvals(s, 1, values);
					if (validinput)
					{
						RENDERSETTINGS->tracerDepth = (int)values[0];
					}

				}else
				if (cmd == "output")
				{
					string output;
					s >> output;
					if (s.fail()) 
					{
						cout << "Failed reading value 'output' will skip\n";							
					}
					s >> output;					

					RENDERSETTINGS->outputFile = output;
					
				}
				else
				if (cmd == "camera")
				{
					validinput = readvals(s, 10, values); 
					if (validinput)
					{
						cam->lookfrom = vec3(values[0], values[1], values[2]);
						cam->lookat = vec3(values[3], values[4], values[5]);
						cam->up = vec3(values[6], values[7], values[8]);
						cam->fovY = values[9];

						cam->PreCalc();

						scene->camPos = cam->lookfrom;
						
					}

				}else // GEOMETRY
				if (cmd == "sphere")
				{
					validinput = readvals(s, 4, values); 
					if (validinput)
					{
						if (scene)
						{
							objectAux = new MySphere(values[0], values[1], values[2], values[3]);
							objectAux->transform = transfstack.top();
							//objectAux->inverseTransform = transfInverseStack.top();
							objectAux->PreCalc();

							scene->AddSphere(dynamic_cast<MySphere*>(objectAux));
							dynamic_cast<MySphere*>(objectAux)->transform = transfstack.top();
							dynamic_cast<MySphere*>(objectAux)->material = materialAux;							
							
						}
					}
				}
				else // Triangle Init
				if (cmd == "maxverts")
				{
					validinput = readvals(s, 1, values); 
					if (validinput)
					{
						if (scene)
						{
							// Only initialize triangle here and also add it to the scene
							scene->SetMaxVerts((int)values[0]);
						}
					}
				}
				else 
				if (cmd == "maxvertnorms")
				{
					validinput = readvals(s, 1, values); 
					if (validinput)
					{
						if (scene)
						{
							scene->SetMaxVertNormal((int)values[0]);
							
						}
					}
				}
				else
				if (cmd == "vertex")
				{
					validinput = readvals(s, 3, values); 
					if (validinput)
					{
						if (scene)
						{							
							scene->AddVertex(vec3(values[0], values[1], values[2]));
						}
					}
				}
				else
				if (cmd == "vertexnormal")
				{
					validinput = readvals(s, 6, values); 
					if (validinput)
					{
						if (scene)
						{
							scene->AddVertexNormal(vec6(values[0], values[1], values[2], values[3], values[4], values[5]));
						}
					}
				}
				else
				if (cmd == "tri")
				{
					validinput = readvals(s, 3, values); 
					if (validinput)
					{
						if (scene)
						{
							
							vec3 vertIndices = vec3(values[0], values[1], values[2]);
							vec4 A = vec4(scene->vertices[(int)values[0]], 1.0f);
							vec4 B = vec4(scene->vertices[(int)values[1]], 1.0f);
							vec4 C = vec4(scene->vertices[(int)values[2]], 1.0f);
							objectAux = new MyTriangle(vertIndices,A, B, C );
							objectAux->transform = transfstack.top();
							
							dynamic_cast<MyTriangle*>(objectAux)->material = materialAux;
							

							dynamic_cast<MyTriangle*>(objectAux)->PreCalc();

							scene->AddTriangle(dynamic_cast<MyTriangle*>(objectAux));

							
						}
					}
				}
				else
				if (cmd == "trinormal")
				{
					validinput = readvals(s, 3, values); 
					if (validinput)
					{
						if (scene)
						{
							/*if (objectAux)
								dynamic_cast<Triangle*>(objectAux)->AddTriFaceNormals(vec3(values[0], values[1], values[2]));						*/
						}
					}

				} // TRANSFORMS
				else 
				if (cmd == "translate") 
				{
					validinput = readvals(s, 3, values);
					if (validinput) 
					{
						float tx = values[0]; float ty = values[1];	float tz = values[2];
						rightmultiply(Transform::translate(tx, ty, tz), transfstack);
						leftmultiply(glm::inverse(Transform::translate(tx, ty, tz)), transfInverseStack);
					}
				}
				else
				if (cmd == "scale") 
				{
					validinput = readvals(s, 3, values);
					if (validinput)
					{
						float sx = values[0]; float sy = values[1];	float sz = values[2];
						rightmultiply(Transform::scale(sx, sy, sz), transfstack);
						leftmultiply(glm::inverse(Transform::scale(sx, sy, sz)), transfInverseStack);
					}
				}
				else
				if (cmd == "rotate") 
				{
					validinput = readvals(s, 4, values);
					if (validinput) 
					{

						vec3 axis = vec3(values[0], values[1], values[2]);
						float theta = values[3];
						mat3 R = Transform::rotate(theta, axis);
						mat4 T = mat4(R[0][0], R[0][1], R[0][2], 0,
							R[1][0], R[1][1], R[1][2], 0,
							R[2][0], R[2][1], R[2][2], 0,
							0, 0, 0, 1);

						rightmultiply(T, transfstack);
						leftmultiply(glm::inverse(T), transfInverseStack);
					}
				}
				else
				if (cmd == "directional")
				{
					validinput = readvals(s, 6, values);
					if (validinput)
					{
						vec3 dir = vec3(values[0], values[1], values[2]);
						vec4 color = vec4(values[3], values[4], values[5], 1.0f);
						lightAux = new Light(directional, dir, color);
						lightAux->attenuation = attenuationAux;
						scene->AddLight(lightAux);
					}
				}
				else
				if (cmd == "point")
				{
					validinput = readvals(s, 6, values);
					if (validinput)
					{
						vec3 pos = vec3(values[0], values[1], values[2]);
						vec4 color = vec4(values[3], values[4], values[5], 1.0f);
						lightAux = new Light(point, pos, color);
						lightAux->attenuation = attenuationAux;
						scene->AddLight(lightAux);
					}
				}
				else
				if (cmd == "attenuation")
				{
					validinput = readvals(s,3, values);
					if (validinput)
					{
						attenuationAux = vec3(values[0], values[1], values[2]);
					}
				}
				else
				if (cmd == "diffuse")
				{
					validinput = readvals(s, 3, values);
					
					if (validinput)
					{
						materialAux.Kd = vec4(values[0], values[1], values[2], 0.0f);
					}
				}
				else
				if (cmd == "specular")
				{
					validinput = readvals(s, 3, values);
					if (validinput)
					{
						materialAux.Ks = vec4(values[0], values[1], values[2], 1.0f);
						
					}
				}
				else
				if (cmd == "shininess")
				{
					validinput = readvals(s, 1, values);
					if (validinput)
					{
						materialAux.shininess = values[0];

					}
				}
				else
				if (cmd == "emission")
				{
					validinput = readvals(s, 3, values);
					if (validinput)
					{
						vec4 emission = vec4(values[0], values[1], values[2], 1.0f);
						materialAux.emission = emission;

					}
				}
				else
					if (cmd == "ambient")
					{
						validinput = readvals(s, 3, values);
						if (validinput)
						{
							vec4 ambient1 = vec4(values[0], values[1], values[2], 0.0f);
							cout << "New  Ambient" << endl;
							materialAux.Ka = ambient1;
							

						}
					}
				// I include the basic push/pop code for matrix stacks
				else
				if (cmd == "pushTransform") 
				{
					transfstack.push(transfstack.top()); 
					
					/*if (objectAux)
					{
						if (objectAux->type == mesh)
						{
							scene->AddTriangle(dynamic_cast<Mesh*>(objectAux));
						}
						else
						{
							scene->AddSphere(dynamic_cast<Sphere*>(objectAux));
						}
					}*/

					objectAux = nullptr;


				}
				else 
				if (cmd == "popTransform") 
				{
					if (transfstack.size() <= 1) 
					{
						cerr << "Stack has no elements.  Cannot Pop\n"; 
					}
					else 
					{
						transfstack.pop(); 
					}
				}
				else 
				{
					cerr << "Unknown Command: " << cmd << " Skipping \n"; 
				}


			}
			

			getline (in, str); 
		} // end while

		
	} else
	{
		cerr << "Unable to Open Input Data File " << filename << "\n"; 
		throw 2; 
	}






}
