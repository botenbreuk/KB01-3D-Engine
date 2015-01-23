#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include <string>
#include <iostream>
#include <Windows.h>

#include "Entity.h"
#include "Renderer.h"
#include "CustomVertex.h"

class Terrain : Entity
{
public:
	Terrain();
	~Terrain();
	void Render(Renderer* renderer); //Renders the heightmap

private:
	bool LoadHeightmap(char* argFileName); //Loads the given hightmap
	void FillVertices(); //Fills the vertices pointer
	void FillIndices(); //Fills the indices pointer

	BITMAP bm; //Holds the bitmap information
	BYTE* heightData; //Holds the color values for the height
	CUSTOMVERTEX* cv_Vertices; //Holds the vertices of the heightmap
	short* s_Indices; //Holds the indeces of the heigtmap
	char* _filePath; //Holds the filepath of the heightmap
};

#endif