#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include <string>
#include <iostream>
#include <Windows.h>

#include "Entity.h"
#include "Renderer.h"
#include "VertexValue.h"

class Terrain : Entity
{
public:
	Terrain();
	~Terrain();
	void Render(Renderer* renderer);

private:
	bool LoadHeightmap(char* argFileName); //Loads the given hightmap
	VERTEXVALUE* FillVertices();
	short* FillIndices();

	BITMAP bm;
	BYTE* heightData; //Holds the color values for the height
};

#endif