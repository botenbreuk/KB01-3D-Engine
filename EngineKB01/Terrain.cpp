#include "Terrain.h"

Terrain::Terrain()
{
	if(LoadHeightmap("heightmap.bmp"))
	{
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

	//Store the width and height of the heightmap
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
	VERTEXVALUE* vertices = FillVertices();
	short* indices = FillIndices();
	
	renderer->SetVertexBuffer(vertices);
	renderer->SetIndexBuffer(indices, vertices);
}

VERTEXVALUE* Terrain::FillVertices()
{
    //VERTEXVALUE* cv_Vertices = new VERTEXVALUE[width*width];

    /*for (int x=0;x< width;x++)
	{
        for (int y = 0; y < height; y++)
		{
            cv_Vertices[y*width + x].x = -x;
            cv_Vertices[y*width + x].y = heightData[y];
            cv_Vertices[y*width + x].z = y;
            cv_Vertices[y*width + x].color = 0xffffffff;
        }
    }*/

	VERTEXVALUE cv_Vertices[] =
    {
        { -1.0f, 1.0f, -1.0f, 0xffffffff, },
        { 1.0f, 1.0f, -1.0f, 0xffffffff, },
        { -1.0f, 1.0f, 1.0f, 0xffffffff, },
        { 1.0f, 1.0f, 1.0f, 0xffffffff, },

		{ -1.0f, -1.0f, -1.0f, 0xffffffff, },
        { 1.0f, -1.0f, -1.0f, 0xffffffff, },
        { -1.0f, -1.0f, 1.0f, 0xffffffff, },
        { 1.0f, -1.0f, 1.0f, 0xffffffff, },
    };

    return cv_Vertices;
}

short* Terrain::FillIndices()
{
    //short *s_Indices = new short[(width-1)*(height-1)*6];

    /*for (int x = 0; x < width-1; x++)
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
    }*/

	short s_Indices[] =
    {
		0, 1, 2,    // side 1
        1, 3, 2,
        4, 0, 6,    // side 2
        6, 0, 2,
        7, 5, 6,    // side 3
        6, 5, 4,
        3, 1, 7,    // side 4
        7, 1, 5,
        4, 5, 0,    // side 5
        0, 5, 1,
        3, 7, 2,    // side 6
        2, 7, 6,
	};

    return s_Indices;
}