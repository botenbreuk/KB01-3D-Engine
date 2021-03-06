#ifndef __RECOURCEMANAGER_H__
#define __RECOURCEMANAGER_H__

#include <map>
#include <list>
#include <utility>
#include <string>

#include "Renderer.h"
#include "Resource.h"
#include "Texture.h"
#include "Mesh.h"
#include "Logger.h"
#include "LoggerPool.h"

class ResourceManager
{
public:
	ResourceManager(Renderer* renderer);
	~ResourceManager();
	Mesh* GetMesh(std::string meshName); //Returns a pointer to the Mesh with the given name.
	Texture* GetTexture(std::string textureName); //Returns a pointer to the Texture with the given name.
	void LoadMeshes();
	void LoadMesh(std::string meshName, std::string filePath); //Loads in a Mesh.
	void LoadTexture(std::string textureName, std::string filePath); //Loads in a Texture.

private:
	bool MeshLoadedIn(std::string filePath); //Checks if the specific Mesh is already loaded in.
	std::string GetMeshName(std::string filePath); //Gives the name of the loaded in Mesh.

	bool TextureLoadedIn(std::string filePath); //Checks if the specific Texture is already loaded in.
	std::string GetTextureName(std::string filePath); //Gives the name of the loaded in Texture.

	std::map<std::string, Mesh*> _meshes; //A Key Value pair list of meshes with the associated names.
	std::map<std::string, Texture*> _textures; //A Key Value pair list of textures with the associated names
	Logger* _logger; //Used for logging errors, warnings and other messages
	Renderer* _renderer;//

};

#endif