#include <iostream>
#include <string>
#define GLM_PRECISION_HIGHP_FLOAT
#define GLM_PRECISION_HIGHP_DOUBLE
#include <glm\glm.hpp>
#include <free_image\FreeImage.h>
#include "RayTracer.h"
#include "readfile.h"
#include "RenderSettings.h"


using namespace std;

void SaveImageFile(MyImage &image, const string & fname)
{
	
	FreeImage_Initialise();

	FIBITMAP * img = FreeImage_Allocate(image.width, image.height, 24);

	if (img)
	{
		RGBQUAD color;

		for (int i = 0; i < image.width; i++)
			for (int j = 0; j < image.height; j++)
			{
				color.rgbRed = image.image[j][i].x;
				color.rgbGreen = image.image[j][i].y;
				color.rgbBlue = image.image[j][i].z;
				FreeImage_SetPixelColor(img, i, j, &color);
			}

		FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);

		//delete img;	

		std::cout << "Saving screenshot: " << fname << "\n";
	}
	else
		std::cout << "Error: Something happened while saving image: " << fname << "\n";	
	
	FreeImage_DeInitialise();
	
}

int main(int argc, char * argv[])
{

	if (argc < 2) 
	{
		cerr << "Usage: transforms scenefile [grader input (optional)]\n";
		exit(-1);
	}

	char * sceneFile = argv[1];

	cout << "Scene File: " << sceneFile << endl;

	string fname = string("imgResult.png");
	
	

	RayTracer tracer;
	
	Camera * cam = new Camera();

	Scene * scene = new Scene();

	readfile(sceneFile, cam, scene);

	MyImage image = tracer.RayTrace(cam, scene, RENDERSETTINGS->width, RENDERSETTINGS->height);

	SaveImageFile(image, "" + RENDERSETTINGS->outputFile);

	system("PAUSE");

	return 0;
}