#ifndef __CUSTOMVERTEX_H__
#define __CUSTOMVERTEX_H__

struct CUSTOMVERTEX
{
    FLOAT x, y, z, rhw; // The transformed position for the vertex
    DWORD color;        // The vertex color
	FLOAT tu, tv;		// The texture coordinates
};

#endif