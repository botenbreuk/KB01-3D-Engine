#include "SceneManager.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

///Renders all the Scenes this Manager knows
void SceneManager::RenderAllScenes(Renderer* renderer, ResourceManager* rsm, std::list<std::pair<Scene*, Window*>> pairs)
{
	std::list<std::pair<Scene*, Window*>>::const_iterator iter;

	for(iter = pairs.begin(); iter != pairs.end(); iter++)
	{
		(*iter).first->Render(renderer, rsm, (*iter).second);
	}
}

///Updates all the Scenes this Manager knows
void SceneManager::UpdateAllScenes()
{
	std::list<Scene*>::const_iterator iter;
	for(iter = _scenes.begin(); iter != _scenes.end(); iter++)
	{
		(*iter)->Update();
	}
}

///Adds a Scene to the Manager's list
Scene* SceneManager::AddScene(ResourceManager* rsm, InputHandler* inputHandler)
{
	Scene* newScene = new Scene(rsm, inputHandler);
	_scenes.push_front(newScene);
	
	return newScene;
}

Scene* SceneManager::AddSceneFromFile(ResourceManager* rsm, std::string filePath, InputHandler* inputHandler)
{
	Scene* newScene = new Scene(rsm, inputHandler);
	newScene->LoadSceneFromFile(filePath, rsm);
	_scenes.push_front(newScene);
	
	return newScene;
}