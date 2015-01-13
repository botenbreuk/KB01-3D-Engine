#include "Scene.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

Scene::Scene(ResourceManager* rsm)
{
	this->LoadSceneFromFile("SceneFile.txt", rsm);
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
void Scene::AddModel(Model* model)
{
	//mod->SetMeshName(_meshName);
	_modelList.push_front(model);
}

///Loads list of models from a file
void Scene::LoadSceneFromFile(std::string fileName, ResourceManager* rsm)
{
	std::ifstream file(fileName);
	std::string line;

	if(CheckFileExists(fileName))
	{
		while(std::getline(file, line))
		{
			std::string temp;
			std::vector<std::string> cds;
			std::stringstream str(line);
			while(str >> temp)
			cds.push_back(temp);

			if(CheckFileExists(cds[0])) 
			{
				float x = std::stof(cds[1]);
				float y = std::stof(cds[2]);
				float z = std::stof(cds[3]);

				Model* model = new Model(rsm, cds[0], true);
				model->SetPosistion(x, y, z);

				AddModel(model);
			}
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