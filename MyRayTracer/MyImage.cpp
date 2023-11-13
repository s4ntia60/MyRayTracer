#include "MyImage.h"
#include <iostream>

using namespace std;

void PrintVector2(char * name, vec3 vec)
{
	cout << name << " x=" << vec.x << " y=" << vec.y << " z=" << vec.z << endl;
}

MyImage::MyImage(int width, int height)
{
	this->width = width;
	this->height= height;

	// create matrix color 
	image = new vec3*[height];

	for (int i = 0; i < height; i++)
	{
		image[i] = new vec3[width];
	}

	// initialise color matrix
	vec3 black = vec3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{

			image[i][j] = black;
			if (i >= 10 && i <= 20)
				image[i][j] = vec3(255, 0, 0);

			if (j >= 10 && j <= 20)
				image[i][j] = vec3(255, 0, 0);
		}		
	}

}


MyImage::~MyImage()
{
}

// Return a 1-D array with the image info as a sequence of bytes
// BYTE * MyImage::ConvertToOneRowArray()
// {
// 	if (!image) 
// 		return nullptr;
//
// 	int size = 3 * width * height;
// 	BYTE *pixels = new BYTE[size];
// 	int row = 0;
// 	int col = 0;
//
// 	// create matrix color 
// 	//vec3 ** imageAux = new vec3*[height];
//
// 	//for (int i = 0; i < height; i++)
// 	//{
// 	//	imageAux[i] = new vec3[width];
// 	//}
//
// 	//for (int i = 0; i < width; i++)
// 	//	for (int j = 0; j < height; j++)
// 	//	{
// 	//		image
// 	//	}
//
//
// 	//for (int i = size-1-3; i >= 0; i -= 3)
// 	for (int i = 0; i < size; i += 3)
// 	{
// 		
// 		//vec3 color;
// 		////std::cout << i << std::endl;
// 		///*if (row > height / 2)
// 		//{*/
// 		//	if (col > width / 2)
// 		//		color = vec3(255, 0, 0);
// 		//	else
// 		//		color = vec3(0, 255, 0);
// 		////}
// 		////else // Mitad superior
// 		//{
// 		//	// derecha
// 		//	if (col > width / 2)
// 		//		color = vec3(0, 0, 255);
// 		//	else
// 		//		color = vec3(255, 255, 0);
// 		//}
//
// 	/*	pixels[i] = color.x;
// 		pixels[i + 1] = color.y;
// 		pixels[i + 2] = color.z; */
// 		pixels[i] = (BYTE)image[row][col].x;
// 		pixels[i + 1] = (BYTE)image[row][col].y;
// 		pixels[i + 2] = (BYTE)image[row][col].z;
// 		//PrintVector2("Image color" , image[row][col]);
//
// 		col++;
//
// 		if (col >= width)
// 		{
// 			col = 0;
// 			row++;			
// 		}
// 	}
//
//
//
// 	/*for (int i = 0; i < size; i+=3)
// 	{
// 		if((int)pixels[i] != 0 || (int)pixels[i+1] != 0 || (int)pixels[i+2] != 0)
// 			cout << "Pixels" << (int)pixels[i] << ", " << (int)pixels[i + 1] << ", " << (int)pixels[i + 2] << ", " << endl;
// 	}*/
// 	return pixels;
// }
