#include "SceneManager.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

///Renders all the Scenes this Manager knows.
void SceneManager::RenderAllScenes(Renderer* renderer, ResourceManager* msm, WindowSceneConnector* wsc)
{
	std::list<std::pair<Scene*, Window*>>::const_iterator iter;
	std::list<std::pair<Scene*, Window*>> pairs = wsc->GetList();

	for(iter = pairs.begin(); iter != pairs.end(); iter++)
	{
		(*iter).first->Render(renderer, msm, (*iter).second);
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
Scene* SceneManager::AddScene(ResourceManager* rsm)
{
	Scene* newScene = new Scene(rsm);
	_scenes.push_front(newScene);
	return newScene;
}

Scene* SceneManager::AddSceneFromFile(ResourceManager* rsm, std::string filePath)
{
	Scene* newScene = new Scene(rsm);
	newScene->LoadSceneFromFile(filePath, rsm);
	_scenes.push_front(newScene);
	return newScene;
}