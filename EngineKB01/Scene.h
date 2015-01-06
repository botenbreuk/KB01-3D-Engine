#ifndef __SCENE_H__
#define __SCENE_H__

#include "entity.h"
#include "model.h"
#include "Renderer.h"
#include "DirectXRenderer.h"
#include "ResourceManager.h"
#include <list>

class Scene
{
public:
	Scene();
	~Scene();
	std::list<Model*> ModelList; //List of models
	std::list<Entity*> EntityList;//The list of Entities this scene holds.
	void Render(Renderer* renderer, ResourceManager* msm);//Renders the Entities in the Scene.
	void AddEntity(Entity* entity);//Adds an Entity to the scene.
	void RemoveEntity(Entity* entity);//Removes a specific Entity from the scene.
	void Update();//Updates the Entities in the Scene,

	void AddModel(std::string _meshName);//Adds a Model to the Scene.
};

#endif