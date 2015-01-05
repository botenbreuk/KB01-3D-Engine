#ifndef __RECOURCEMANAGER_H__
#define __RECOURCEMANAGER_H__

#include "Resource.h"
#include "Texture.h"
#include <map>
#include <utility>
#include "Mesh.h"
#include "Log.h"
#include <string>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	//Mesh* GetMesh(std::string meshName);//Returns a pointer to the Mesh with the given name.
	//void LoadMesh(std::string meshName, std::string filePath);//Loads in a Mesh.
	//Texture* GetTexture(std::string textureName);//Returns a pointer to the Texture with the given name.
	//void LoadTexture(std::string textureName, std::string filePath);//Loads in a Texture.

protected:
	Log* Logger;
};

#endif