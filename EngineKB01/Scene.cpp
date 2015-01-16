#include "Scene.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

Scene::Scene(ResourceManager* rsm)
{
	this->LoadSceneFromFile("SceneFile.txt", rsm);
	this->_skyBox = new Skybox();
	terrain = new Terrain();
}


Scene::~Scene()
{
	delete _skyBox;
}

///Tells all entities in this scene to render themselves.
///renderer: A pointer to the renderer used.
void Scene::Render(Renderer* renderer, ResourceManager* msm, Window* window)
{
	terrain->Render(renderer);
	//Clear buffers and begin rendering
	
	renderer->SetTargetSwapChain(window->GetHWND());
	renderer->ClearScreen();
	renderer->BeginScene();
	_skyBox->Render(renderer);
	renderer->SetupWorldMatrix();
	renderer->SetupViewMatrix(-18.0f);
	renderer->SetupProjectionMatrix();

	

	std::list<Model*>::const_iterator iter;
	for(iter = _modelList.begin(); iter != _modelList.end(); iter++)
	{
		(*iter)->Render(renderer, msm);
	}

	//Ends rendering
	renderer->EndScene();
	renderer->Present(window->GetHWND());
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
	if(CheckFileExists(fileName))
	{
		_modelList.clear();
		std::ifstream file(fileName);
		std::string line;
	
		while(std::getline(file, line))
		{
			std::string temp;
			std::vector<std::string> cds;
			std::stringstream str(line);
			while(str >> temp)
			cds.push_back(temp);

			if(CheckFileExists(cds[0])) 
			{
				Model* model = new Model(rsm, cds[0], true);
				if(cds.size() > 1)
				{
					float x = std::stof(cds[1]);
					float y = std::stof(cds[2]);
					float z = std::stof(cds[3]);

					model->SetPosition(x, y, z);
				}
				else model->SetPosition();

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