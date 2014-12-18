#include "Scene.h"


Scene::Scene()
{
	this->EntityList = new std::list<Entity>;//Defines the list of entities.
}


Scene::~Scene()
{
	delete EntityList;//Destroys the list, it's content and the pointer.
}

/*
Renders the scene and the entities in it.
renderer: A pointer to the renderer used.
*/
void Scene::RenderScene(Renderer* renderer)
{
	//TOTO: Implement
}

/*
Adds an entity to the scene.
entity: A pointer to the entity that is to be added.
*/
void Scene::AddEntity(Entity* entity)
{
	//TODO: Implement
}

/*
Removes a specific entity from the scene.
entity: A pointer to the entity that is to be removed.
*/
void Scene::RemoveEntity(Entity* entity)
{
	//TODO: Implement
}