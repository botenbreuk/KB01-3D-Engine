#ifndef __RENDERER_H__
#define __RENDERER_H__
#include <string>

class Renderer
{
public:
	virtual ~Renderer();
	virtual void RenderMesh(std::string meshPath) = 0;//Method called to render a mesh, implementation happens in subclasses.
	virtual void RenderTexture(std::string texturePath) = 0;//Method called to render a texture, implementation happens in subclasses.
};

#endif