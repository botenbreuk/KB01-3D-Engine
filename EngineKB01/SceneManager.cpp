#include "SceneManager.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

///Renders all the Scenes this Manager knows.
void SceneManager::RenderAllScenes(Renderer* renderer, ResourceManager* msm)
{
	std::list<Scene*>::const_iterator iter;
	for(iter = _scenes.begin(); iter != _scenes.end(); iter++)
	{
		(*iter)->Render(renderer, msm);
	}
}

///Renders all the Scenes this Manager knows.
void SceneManager::UpdateAllScenes()
{
	std::list<Scene*>::const_iterator iter;
	for(iter = _scenes.begin(); iter != _scenes.end(); iter++)
	{
		(*iter)->Update();
	}
}

///Adds a Scene to the Manager's list.
Scene* SceneManager::AddScene()
{
	Scene* newScene = new Scene();
	_scenes.push_front(newScene);
	return newScene;
}