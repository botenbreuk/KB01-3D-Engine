#include "Terrain.h"

Terrain::Terrain()
{
	if(LoadHeightmap("heightmap.bmp"))
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

void Terrain::Render(Renderer* renderer)
{
	int width = bm.bmWidth;
	
	renderer->SetModelMatrix(0, 0, 0, 1, 0);
	//renderer->SetVertexBuffer(cv_Vertices, width*width);
	//renderer->SetIndexBuffer(s_Indices, width*width*3);
}

void Terrain::FillVertices()
{
	int width = bm.bmWidth;
	int height = bm.bmWidth;

	cv_Vertices = new CUSTOMVERTEX[width*width];

    for (int x=0;x< width;x++)
	{
        for (int y = 0; y < height; y++)
		{
            cv_Vertices[y*width + x].x = -x;
            cv_Vertices[y*width + x].y = heightData[y];
            cv_Vertices[y*width + x].z = y;
            cv_Vertices[y*width + x].rhw = 1.0f;
            cv_Vertices[y*width + x].color = 0xffffffff;
        }
    }
}

void Terrain::FillIndices()
{
	int width = bm.bmWidth;
	int height = bm.bmWidth;

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