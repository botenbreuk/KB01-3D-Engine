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
	void RenderAllScenes(Renderer* renderer);//Renders all the Scenes this Manager knows.
	void UpdateAllScenes();//Updates all the Scenes this Manager knows.

private:
	std::list<Scene*> Scenes;
};

#endif