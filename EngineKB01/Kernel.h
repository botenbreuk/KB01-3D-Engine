#ifndef __KERNEL_H__
#define __KERNEL_H__

#include <iostream>
#include <stdio.h>
#include <list>
#include <map>

#include "ResourceManager.h"
#include "WindowManager.h"
#include "SceneManager.h"
#include "DirectXRenderer.h"
#include "LoggerPool.h"
#include "DirectXInputHandler.h"
#include "Scene.h"
#include "Window.h"

class Kernel
{
public:
	Kernel();
	~Kernel();
	void RunBasic();//Initializes and runs the basic loop of the Engine.
	void CleanUp();//Cleans up the compartments of the Engine.
	enum APIType {DirectX = 0, OpenGL = 1, Software = 2, First = DirectX, Last = Software};//The different types of renderers the kernel knows and can use.
	void AddConnection(Scene* scene, Window* window);

	//Methods for expert interface
	void CreateResourceManager();
	void CreateWindowManager();
	void CreateSceneManager();
	void LoadRenderer();
	void Start();

private:
	std::map<APIType, Renderer*> _renderers;		//The Renderers the Engine uses.
	ResourceManager* _resourceManager;				//The general Rescource Manager.
	WindowManager* _windowManager;					//The Window Manager the Engine uses
	SceneManager* _sceneManager;					//The Scene Manager the Engine uses.
	Logger* _logger;								//A logger for writing to the logfile.
	APIType _usedType;								//The type of API the engine uses.
	InputHandler * _inputHandler;					//The InputHandler the Engine uses.
	std::list<std::pair<Scene*, Window*>> _pairs;	//List of Windows with Scenes
};

#endif