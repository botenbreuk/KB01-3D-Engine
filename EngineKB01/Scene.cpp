#include "Scene.h"


Scene::Scene(void)
{
	this->EntityList = new std::list<Entity>;//Defines the list of entities.
}


Scene::~Scene(void)
{
	EntityList->~list();//Destroys the list and it's content.
}

/*
Renders the scene and the entities in it.
*/
void Scene::Render(Renderer* renderer)
{
	//TOTO: Implement
}

/*
Adds an entity to the scene.
*/
void Scene::AddEntity(Entity* entity)
{
	//TODO: Implement
}

/*
Removes a specific entity from the scene.
*/
void Scene::RemoveEntity(Entity* entity)
{
	//TODO: Implement
}