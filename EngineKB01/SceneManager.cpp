#include "SceneManager.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

/*
Renders all the Scenes this Manager knows.
*/
void SceneManager::RenderAllScenes(Renderer* renderer)
{
	std::list<Scene*>::const_iterator iter;
	for(iter = Scenes.begin(); iter != Scenes.end(); iter++)
	{
		(*iter)->RenderScene(renderer);
	}
}

/*
Renders all the Scenes this Manager knows.
*/
void SceneManager::UpdateAllScenes()
{
	std::list<Scene*>::const_iterator iter;
	for(iter = Scenes.begin(); iter != Scenes.end(); iter++)
	{
		(*iter)->UpdateScene();
	}
}