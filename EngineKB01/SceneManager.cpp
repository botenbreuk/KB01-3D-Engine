#include "SceneManager.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::RenderAllScenes(Renderer* renderer){
	std::list<Scene*>::const_iterator iter;
	for(iter = Scenes.begin(); iter != Scenes.end(); iter++)
	{

	}
}

void SceneManager::UpdateAllScenes(){

}