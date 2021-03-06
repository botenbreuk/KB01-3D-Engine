#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include <list>

#include "Scene.h"
#include "DirectXRenderer.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void RenderAllScenes(Renderer* renderer, ResourceManager* rsm, std::list<std::pair<Scene*, Window*>> pairs); //Renders all the Scenes this Manager knows.
	void UpdateAllScenes(); //Updates all the Scenes this Manager knows.
	Scene* AddScene(ResourceManager* rsm, InputHandler* inputHandler); //Adds a Scene to the Manager's list.
	Scene* AddSceneFromFile(ResourceManager* rsm, std::string filePath, InputHandler* inputHandler); //Adds a Scene with a specific filepath to the Manager's list.

private:
	std::list<Scene*> _scenes; //All the Scenes this Manager knows.
};

#endif