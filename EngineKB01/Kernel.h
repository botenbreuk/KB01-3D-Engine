#ifndef __KERNEL_H__
#define __KERNEL_H__

#include <iostream>
#include <stdio.h>

#include "ResourceManager.h"
#include "MeshManager.h"
#include "WindowManager.h"
#include "SceneManager.h"
#include "DirectXRenderer.h"
#include "Log.h"

class Kernel
{
public:
	Kernel();
	~Kernel();
	void Initialize();//Initialises the compartments of the Engine.
	void Run();//The basic loop of the Engine.
	void CleanUp();//Cleans up the compartments of the Engine.
	enum RendererType {DirectX = 0, OpenGL = 1, Software = 2, First = DirectX, Last = Software};//The different types of renderers the kernel knows and can use.

private:
	std::map<RendererType, Renderer*> _renderers;//The Renderer the Engine uses.
	ResourceManager* _resourceManager;//The general Rescource Manager.
	MeshManager* _meshManager;//Temporal Mesh Manager, will be refactored into the one Rescource Manager.
	WindowManager* _windowManager;//The Window Manager the Engine uses
	SceneManager* _sceneManager;//The Scene Manager the Engine uses.
	Log* _logger;//A logger for writing to the logfile.
	RendererType _usedType;
};

#endif