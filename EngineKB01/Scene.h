#ifndef __SCENE_H__
#define __SCENE_H__

#include "entity.h"
#include <list>

class Scene
{
public:
	Scene();
	~Scene();
	std::list<Entity>* EntityList;//The list of entities this scene holds.
	void RenderScene(Renderer* renderer);//Renders the scene and the entities in it.
	void AddEntity(Entity* entity);//Adds an entity to the scene.
	void RemoveEntity(Entity* entity);//Removes a specific entity from the scene.
};

#endif