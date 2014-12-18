#ifndef __RENDERER_H__
#define __RENDERER_H__
#include <string>

class Renderer
{
public:

	//virtual 3DDEVICE WIP: not directx only.
	
	virtual ~Renderer(void);
	virtual void RenderMesh(std::string meshPath) = 0;//Method called to render a mesh, implementation happens in subclasses.
	virtual void RenderTexture(std::string texturePath) = 0;//Method called to render a texture, implementation happens in subclasses.
protected:
	//LPDIRECT3DDEVICE9   g_pd3dDevice;
};

#endif