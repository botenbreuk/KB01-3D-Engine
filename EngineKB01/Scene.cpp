#include "Scene.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

Scene::Scene(ResourceManager* rsm, InputHandler* inputHandler)
{
	LoadSceneFromFile("SceneFile.txt", rsm);
	this->_skyBox = new Skybox();
	this->_terrain = new Terrain();
	_inputHandler = inputHandler;
	_logger = LoggerPool::GetInstance()->GetLogger("Scene");
}

Scene::~Scene()
{	
	delete _skyBox;
}

///Tells all entities in this scene to render themselves.
///renderer: A pointer to the renderer used.
void Scene::Render(Renderer* renderer, ResourceManager* msm, Window* window)
{
	//Clear buffers and begin rendering
	
	renderer->SetTargetSwapChain(window->GetHWND());
	renderer->ClearScreen();
	renderer->BeginScene();
	renderer->SetupWorldMatrix();
	renderer->SetupViewMatrix(-18.0f);
	renderer->SetupProjectionMatrix();
	_terrain->Render(renderer);
	_skyBox->Render(renderer);
	
	std::list<Model*>::const_iterator iter;
	for(iter = _models.begin(); iter != _models.end(); iter++)
	{
		(*iter)->Render(renderer, msm);
	}

	//Ends rendering
	renderer->EndScene();
	renderer->Present(window->GetHWND());
}

///Updates the Entities in the Scene.
void Scene::Update(){
	_inputHandler->Update();

	std::list<Entity*>::const_iterator iter;
	for(iter = _entities.begin(); iter != _entities.end(); iter++)
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
	_models.push_front(model);
}

///Loads list of models from a file
void Scene::LoadSceneFromFile(std::string fileName, ResourceManager* rsm)
{
	if(CheckFileExists(fileName))
	{
		_models.clear();
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
					if(cds.size() > 4)
					{
						float scale = std::stof(cds[4]);
						float rotation = std::stof(cds[5]);

						model->SetScale(scale);
						model->SetRotation(rotation);
					}

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

///Check if the file exists
///param filename
///return: bool
bool Scene::CheckFileExists(std::string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}