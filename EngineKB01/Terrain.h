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
	void Render(Renderer* renderer);

private:
	bool LoadHeightmap(char* argFileName); //Loads the given hightmap
	void FillVertices();
	void FillIndices();

	BITMAP bm;
	BYTE* heightData; //Holds the color values for the height
	CUSTOMVERTEX* _Vertices;
	short _Indices[];
};

#endif