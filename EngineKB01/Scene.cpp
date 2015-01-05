#include "Scene.h"


Scene::Scene()
{
	AddModel("tiger.x");
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
void Scene::Render(Renderer* renderer, MeshManager* msm)
{

	//Clear buffers and begin rendering
	renderer->ClearScreen();
	renderer->BeginScene();
	
	renderer->SetupMatrices();

	std::list<Model*>::const_iterator iter;
	for(iter = ModelList.begin(); iter != ModelList.end(); iter++)
	{
		(*iter)->Render(renderer, msm);
	}

	//Ends rendering
	renderer->EndScene();
	renderer->Present();
}

/*
Updates the Entities in the Scene.
*/
void Scene::Update(){
	std::list<Entity*>::const_iterator iter;
	for(iter = EntityList.begin(); iter != EntityList.end(); iter++)
	{
		(*iter)->Update();
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

void Scene::AddModel(std::string _meshName)
{
	Model* mod = new Model();
	mod->SetMeshName(_meshName);
	ModelList.push_front(mod);
}