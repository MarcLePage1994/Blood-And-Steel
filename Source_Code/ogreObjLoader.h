#pragma once 

#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreDataStream.h>
#include "bullet-2.82-r2704\src\btBulletCollisionCommon.h"
#include "MathClass.h"
//First, let’s create a data structure to hold our object's data
typedef struct objData
{
	Vec3f vertex;
}DATA;

//Then, our simplest primitive: a triangle (stores the indinces of the data)
typedef struct objTriangles
{
	Vec3f t_vertexIndex;
}TRIANGLE;

//Finally, our object
typedef struct objOject
{
	int maxTriangles;
	TRIANGLE *triangle;
	DATA *points; 
}OBJECT;

/////////////////////////////////////////////////////////////////////////////////

class objLoader
{
public:
	objLoader()
	{
		numTriangles = 0;
	}
	~objLoader()
	{
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////

	void LoadOBJ(char *filename, int maxTriangles)
	{	
		vertices.push_back(Vec3f(0,0,0));
		Ogre::DataStreamPtr pStream = Ogre::ResourceGroupManager::getSingleton().openResource(filename, "General");
		while(!pStream->eof())
		{
			Ogre::String data = pStream->getLine();
			if(data.size() == 0)
			{
			}
			else if(data[0] == 'v' && data[1] == ' ')
			{
				const char* temp = data.c_str();
				float x, y, z;
				sscanf_s(temp, "%*[^ ]%f %f %f", &x, &y, &z);
				Vec3f vertex(x,y,z);
				vertices.push_back(vertex);
			}
			else if(data[0] == 'f')
			{
				const char* temp = data.c_str();
				int x, y, z, a,b,c,d,e,f;
				sscanf_s(temp, "%*[^ ]%i/%i/%i %i/%i/%i %i/%i/%i", &x,&a,&b,&y,&c,&d, &z,&e,&f);
				Vec3f faceIndex(x,y,z);
				faces.push_back(faceIndex);
				numTriangles++;
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////

	std::vector<Vec3f> vertices;
	std::vector<Vec3f> faces;
	//these arrays represent the final sorted data to be sent to the vbo
	float *vertex; //3 values per vertex
	float *normals;//3 values per vertex
	float *texcoords;//2 values per vertex

	float *jointWeights;	//4 values per vertex
	float *jointIndices;	//4 values per vertex

	int jointIndex;
	int vertexIndex;
	int numTriangles;
	int normalIndex;
	int uvIndex;

	//for loading data from file
	OBJECT model;
	FILE *objFile;
	Vec3f XYZ;
	Vec3f _normal;
	Vec3f _textUV;
	Vec3f f_vertexIndex;	
	Vec3f f_uvIndex;
	Vec3f f_normalIndex;
	char line[255];
	char info;	//info that is needed to determine where the input will be stored. 
};
