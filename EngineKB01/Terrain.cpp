#include "Terrain.h"

Terrain::Terrain()
{
	//Sets the filepath
	_filePath = "island-heightmap.bmp";

	//Loads the heigtmap and checks if the heigtmap is loaded
	if(LoadHeightmap(_filePath))
	{
		FillVertices();
		FillIndices();
	}
}

Terrain::~Terrain() {}

bool Terrain::LoadHeightmap(char* argFileName)
{
	//Load image from file
	HDC lhdcDest;	//Handle to Device Context (Windows GDI)
	HANDLE hbmp;	//Handle to an object (standard handle)

	//Create a memory device context compatible with the specified device (NULL)
	lhdcDest = CreateCompatibleDC(NULL);
	if (lhdcDest == NULL)	 
	{		  
		DeleteDC(lhdcDest);	//Delete the DC (prevents a memory leak!)
		return false;		//Jump out of the function
	}

	//Windows GDI load image of type BMP (fileformat)
	hbmp = LoadImageA(NULL, argFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbmp == NULL)	//Give a visual warning if the loading of the image failed
	{
		char s[100];
		wsprintfA(s, "Can't find HeightMask %s", argFileName);
		MessageBoxA(NULL, s, "ERROR ERROR ERROR", MB_OK);
		return false;		//Jump out of the function
	}
	//At this point it is sure that lhdcDest & hbmp are valid.

	//Load the bmp into the device context (memory space)
	SelectObject(lhdcDest, hbmp);

	//The GetObject function retrieves information for the specified graphics object
	//bm is cast to a "void*" because GetObject function doesn't 'know' it's format 
	//(don't know what it is, but just put it in that buffer)
	GetObject(hbmp, sizeof(BITMAP), (void*)&bm);

	//Store the wid5th and height of the heightmap
	int width = bm.bmWidth;
	int height = bm.bmHeight;

	//Create an array to hold all the heightdata
	heightData = new BYTE[width*width];

	//Iterate through the BMP-file and fill the heightdata-array
	for (int lHeight = 0; lHeight < width; lHeight++)
	{
		for (int lWidth = 0; lWidth < width; lWidth++)
		{
			heightData[(lHeight*width)+lWidth] = GetRValue(GetPixel(lhdcDest, lHeight, lWidth));
		}
	}
	//How to optimize this function? (hint: heightmaps are grayscale BMP's)
	return true;
}

///Renders the heightmap
///renderer: pointer to the abstract renderer
///return: void
void Terrain::Render(Renderer* renderer)
{
	//Width of the heigthmap
	int width = bm.bmWidth;
	
	//Creates a model space to draw the terrain in
	renderer->SetModelMatrix(0, -30, 0, 0.5, timeGetTime() / 10000.0f);
	//Creates the vertexbuffer
	renderer->SetVertexBuffer(cv_Vertices, width*width);
	//Creates the indexbuffer
	renderer->SetIndexBuffer(s_Indices, width*width, (width-1)*(width-1)*6);
}

///Fills the vertices pointer
///return: void
void Terrain::FillVertices()
{
	//Width of the bmp for the for loop
	int width = bm.bmWidth;
	////Height of the bmp for the for loop
	int height = bm.bmWidth;

	//Create CUSTOMVERTEX array to store the vertices
	cv_Vertices = new CUSTOMVERTEX[width*width];

    for (int x = 0; x < width; x++)
	{
		int xPos = -(width / 2);
		xPos += x;
        for (int y = 0; y < height; y++)
		{
			int yPos = -(height / 2);
			yPos += y;
            cv_Vertices[y*width + x].x = xPos;
            cv_Vertices[y*width + x].y = heightData[y*width + x] / 5;
            cv_Vertices[y*width + x].z = yPos;
            cv_Vertices[y*width + x].rhw = 1.0f;
            cv_Vertices[y*width + x].color = 0xffffffff;
            cv_Vertices[y*width + x].tu = 0.180;
            cv_Vertices[y*width + x].tv = 0.680;						
        }
    }
}

///Fills the indeces pointer
///return: void
void Terrain::FillIndices()
{
	//Width of the bmp for the for loop
	int width = bm.bmWidth;
	////Height of the bmp for the for loop
	int height = bm.bmWidth;

	//Create short array to store the indices
    s_Indices = new short[(width-1)*(height-1)*6];

    for (int x = 0; x < width-1; x++)
	{
        for (int y = 0; y < height-1; y++)
		{
            s_Indices[(x+y*(width-1))*6+2] = x+y*width;
            s_Indices[(x+y*(width-1))*6+1] = (x+1)+y*width;
            s_Indices[(x+y*(width-1))*6] = (x+1)+(y+1)*width;

            s_Indices[(x+y*(width-1))*6+3] = (x+1)+(y+1)*width;
            s_Indices[(x+y*(width-1))*6+4] = x+y*width;
            s_Indices[(x+y*(width-1))*6+5] = x+(y+1)*width;
        }
    }
}