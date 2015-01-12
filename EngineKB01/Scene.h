#ifndef __SCENE_H__
#define __SCENE_H__

#include "entity.h"
#include "Window.h"
#include "model.h"
#include "Renderer.h"
#include "DirectXRenderer.h"
#include "ResourceManager.h"
#include <list>

class Scene
{
public:
	Scene(ResourceManager* rsm);
	~Scene();
	std::list<Model*> _modelList; //List of models
	std::list<Entity*> _entityList;//The list of Entities this scene holds.
	void Render(Renderer* renderer, ResourceManager* msm, Window* window);//Renders the Entities in the Scene.
	void AddEntity(Entity* entity);//Adds an Entity to the scene.
	void RemoveEntity(Entity* entity);//Removes a specific Entity from the scene.
	void Update();//Updates the Entities in the Scene,

	void AddModel(std::string _meshName, ResourceManager* rsm);//Adds a Model to the Scene.


private:
	void LoadSceneFromFile(std::string fileName, ResourceManager* rsm);//Loads list of models from a file
	bool CheckFileExists(std::string fileName);
};

#endif