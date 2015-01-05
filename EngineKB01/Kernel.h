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

private:
	Renderer* _renderer;//The Renderer the Engine uses.
	ResourceManager* _resourceManager;//The general Rescource Manager.
	MeshManager* _meshManager;//Temporal Mesh Manager, will be refactored into the one Rescource Manager.
	WindowManager* _windowManager;//The Window Manager the Engine uses
	SceneManager* _sceneManager;//The Scene Manager the Engine uses.
};

#endif