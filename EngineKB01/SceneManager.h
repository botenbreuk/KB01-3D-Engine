#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include <list>
#include "Scene.h"
#include "DirectXRenderer.h"
#include "WindowSceneConnector.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void RenderAllScenes(Renderer* renderer, ResourceManager* msm, WindowSceneConnector* wsc);//Renders all the Scenes this Manager knows.
	void UpdateAllScenes();//Updates all the Scenes this Manager knows.
	Scene* AddScene(ResourceManager* rsm);//Adds a Scene to the Manager's list.

private:
	std::list<Scene*> _scenes;//All the Scenes this Manager knows.
};

#endif