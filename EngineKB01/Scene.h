#ifndef __SCENE_H__
#define __SCENE_H__

#include <list>
#include <vector>

#include "entity.h"
#include "Window.h"
#include "model.h"
#include "Skybox.h"
#include "Renderer.h"
#include "DirectXRenderer.h"
#include "ResourceManager.h"
#include "Terrain.h"
#include "InputHandler.h"

class Scene
{
public:
	Scene(ResourceManager* rsm, InputHandler* inputHandler);
	~Scene();
	std::list<Model*> _models; //List of models
	std::list<Entity*> _entities;//The list of Entities this scene holds.
	void Render(Renderer* renderer, ResourceManager* msm, Window* window);//Renders the Entities in the Scene.
	void AddEntity(Entity* entity);//Adds an Entity to the scene.
	void RemoveEntity(Entity* entity);//Removes a specific Entity from the scene.
	void Update();//Updates the Entities in the Scene,
	void LoadSceneFromFile(std::string fileName, ResourceManager* rsm); //Loads list of models from a file
	void AddModel(Model* model);//Adds a Model to the Scene.

private:
	bool CheckFileExists(std::string fileName);
	
	Skybox* _skyBox; //Skybox for this scene
	Terrain* _terrain;

	InputHandler* _inputHandler;

	Logger* _logger;
};

#endif