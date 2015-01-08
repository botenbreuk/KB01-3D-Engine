#include "Scene.h"
#include <fstream>

Scene::Scene()
{
	LoadSceneFromFile("SceneFile.txt");
}


Scene::~Scene()
{
}

///Tells all entities in this scene to render themselves.
///renderer: A pointer to the renderer used.
void Scene::Render(Renderer* renderer, ResourceManager* msm)
{

	//Clear buffers and begin rendering
	renderer->ClearScreen();
	renderer->BeginScene();
	
	renderer->SetupMatrices();

	std::list<Model*>::const_iterator iter;
	for(iter = _modelList.begin(); iter != _modelList.end(); iter++)
	{
		(*iter)->Render(renderer, msm);
	}

	//Ends rendering
	renderer->EndScene();
	renderer->Present();
}

///Updates the Entities in the Scene.
void Scene::Update(){
	std::list<Entity*>::const_iterator iter;
	for(iter = _entityList.begin(); iter != _entityList.end(); iter++)
	{
		(*iter)->Update();
	}
}

///Adds an entity to the scene.
///entity: A pointer to the entity that is to be added.
void Scene::AddEntity(Entity* entity)
{
	//TODO: Implement
}

///Removes a specific entity from the scene.
///entity: A pointer to the entity that is to be removed.
void Scene::RemoveEntity(Entity* entity)
{
	//TODO: Implement
}

///Adds a Model to the Scene.
///_meshName: The name for the Model's Mesh.
void Scene::AddModel(std::string _meshName)
{
	Model* mod = new Model();
	mod->SetMeshName(_meshName);
	_modelList.push_front(mod);
}

void Scene::LoadSceneFromFile(std::string fileName)
{
	std::ifstream file(fileName);
	std::string line;

	if(CheckFileExists(fileName))
	{
		while(std::getline(file, line))
		{
			if(CheckFileExists(line)) AddModel(line);
			else std::cout << "File not found: " << line;
		}
	}
	else std::cout << "Scene file not found: " << fileName;
}

bool Scene::CheckFileExists(std::string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}