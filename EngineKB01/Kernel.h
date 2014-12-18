#ifndef __KERNEL_H__
#define __KERNEL_H__

#include <iostream>
#include <stdio.h>

#include "ResourceManager.h"
#include "MeshManager.h"
#include "WindowManager.h"
#include "DirectXRenderer.h"
#include "Scene.h"

class Kernel
{
public:
	Kernel();
	~Kernel();
	void Initialize();
	void Run();
	void CleanUp();

private:
	Renderer* _renderer;
	ResourceManager* _resourceManager;
	MeshManager* _meshManager;
	WindowManager* _windowManager;
};

#endif