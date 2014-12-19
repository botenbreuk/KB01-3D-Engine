#include "Scene.h"


Scene::Scene()
{
	//this->EntityList = new std::list<Entity*>;//Defines the list of entities.
}


Scene::~Scene()
{
	//delete EntityList;//Destroys the list, it's content and the pointer.
}

/*
Renders the Entities in the Scene.
renderer: A pointer to the renderer used.
Tells all entities in this scene to render themselves
*/
void Scene::RenderScene(Renderer* renderer)
{

	//Clear buffers and begin rendering
	renderer->ClearScreen();
	renderer->BeginScene();
	
	renderer->SetupMatrices();

	std::list<Entity*>::const_iterator iter;
	for(iter = EntityList.begin(); iter != EntityList.end(); iter++)
	{
		//(iter)->Render();
		
		//To Do: call entities to render themselves
	}

	//Ends rendering
	renderer->EndScene();
	renderer->Present();
}

/*
Updates the Entities in the Scene.
*/
void Scene::UpdateScene(){
	std::list<Entity*>::const_iterator iter;
	for(iter = EntityList.begin(); iter != EntityList.end(); iter++)
	{
		//(iter)->Update();
		//To Do: implement
	}
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