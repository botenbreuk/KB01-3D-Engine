#ifndef __SCENE_H__
#define __SCENE_H__

#include "entity.h"
#include "Renderer.h"
#include "DirectXRenderer.h"
#include <list>

class Scene
{
public:
	Scene();
	~Scene();
	std::list<Entity*> EntityList;//The list of Entities this scene holds.
	void Render(Renderer* renderer);//Renders the Entities in the Scene.
	void AddEntity(Entity* entity);//Adds an Entity to the scene.
	void RemoveEntity(Entity* entity);//Removes a specific Entity from the scene.
	void Update();//Updates the Entities in the Scene,
};

#endif