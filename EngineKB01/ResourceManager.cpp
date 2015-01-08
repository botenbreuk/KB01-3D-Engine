#include "ResourceManager.h"

ResourceManager::ResourceManager(Logger* logger, Renderer* renderer)
{
	_logger = logger;
	_renderer = renderer;

	Mesh* tigerX = new Mesh("Tiger.x");
	_meshes["Tiger.x"] = tigerX;
}

ResourceManager::~ResourceManager()
{
}

///Returns a Mesh pointer.
///meshName: The key name of the Mesh.
Mesh* ResourceManager::GetMesh(std::string meshName)
{
	return _meshes[meshName];
}

///Returns a Texture pointer.
///textureName: The key name of the Texture.
Texture* ResourceManager::GetTexture(std::string textureName)
{
	return _textures[textureName];
}

///Loads in a Mesh.
///meshName: The Key name of the Mesh.
///filePath: The filepath to the Mesh.
void ResourceManager::LoadMesh(std::string meshName, std::string filePath)
{
	//Initialises several strings that can be sent to the log.
	std::string succesString = "Mesh: '" + meshName + "' loaded in as '" + filePath + "'.";//Gets in the log if the Mesh is loaded in without any problems.
	std::string failString1 = "A Mesh with the name: '" + meshName + "' already exists.";//Gets in the log if that Key value is already taken in the list.
	std::string failString2 = "That Mesh is already loaded in with the name: '";//Gets in the log if that Mesh is already loaded in.

	//Initialises the char* that will be written to the log.
	char* message;

	//Checks if there is alreay a Mesh with that name.
	if(NULL == _meshes[meshName])
	{
		//Checks if the specific Mesh is already loaded in.
		if(!MeshLoadedIn(filePath))
		{
			//Loads in the Mesh.
			Mesh* m = new Mesh(filePath);
			_meshes[meshName] = m;
			
			//Converts succesString to a Char* and writes it to the log.
			_logger->WriteLog(succesString, Logger::MessageType::Info);
		}
		else
		{
			//Mesh already loaded in
			_logger->WriteLog(failString2 + " " + GetMeshName(filePath) + "'.", Logger::MessageType::Error);
		}

	}
	else
	{
		//Mesh already loaded with that name
		_logger->WriteLog(failString1, Logger::MessageType::Error);
	}
}

///Loads in the Meshes.
void ResourceManager::LoadMeshes()
{
	std::list<Mesh*> meshList;

	std::map<std::string, Mesh*>::const_iterator iter;
	for(iter = _meshes.begin(); iter != _meshes.end(); iter++)
	{
		meshList.push_front(iter->second);
	}

	_renderer->InitGeometry(meshList);
}

///Checks if the specific Mesh is already loaded in.
///filePath: The filepath to the Mesh.
bool ResourceManager::MeshLoadedIn(std::string filePath)
{
	bool loadedIn = false;
	std::map<std::string, Mesh*>::iterator it;
	for(it = _meshes.begin(); it != _meshes.end(); it++)
	{
		if(it->second != NULL)
		{
			if(it->second->GetFilePath().compare(filePath) == 0)
			{
				loadedIn = true;
				break;
			}
		}
	}
	return loadedIn;
}

///Gives the name of the loaded in Mesh.
///filePath: The filepath to the loaded in Mesh.
std::string ResourceManager::GetMeshName(std::string filePath)
{
	std::map<std::string, Mesh*>::iterator it;
	for(it = _meshes.begin(); it != _meshes.end(); it++)
	{
		if(it->second != NULL)
		{
			if(it->second->GetFilePath().compare(filePath) == 0)
			{
				return it->first;
			}
		}
	}
}

///Loads in a Texture.
///textureName: The Key name of the Texture.
///filePath: The filepath to the Texture.
void ResourceManager::LoadTexture(std::string textureName, std::string filePath)
{
	//Initialises several strings that can be sent to the log.
	std::string succesString = "Texture: '" + textureName + "' loaded in as '" + filePath + "'.";//Gets in the log if the Texture is loaded in without any problems.
	std::string failString1 = "A Texture with the name: '" + textureName + "' already exists.";//Gets in the log if that Key value is already taken in the list.
	std::string failString2 = "That Texture is already loaded in with the name: '";//Gets in the log if that Texture is already loaded in.

	//Initialises the char* that will be written to the log.
	char* message;

	if(NULL == _textures[textureName])//Checks if there isn't a Texture with that name already.
	{
		if(!TextureLoadedIn(filePath))//Checks if the specific Texture is already loaded in.
		{
			//Loads in the Texture.
			Texture* t = new Texture(filePath);
			_textures[textureName] = t;

			//Converts succesString to a Char* and writes it to the log.
			_logger->WriteLog(succesString, Logger::MessageType::Info);
		}
		else
		{
			//Texture already loaded in
			_logger->WriteLog(failString2 + " " + GetTextureName(filePath) + "'.", Logger::MessageType::Error);
		}

	}
	else
	{
		//texture already loaded with that name
		_logger->WriteLog(failString1, Logger::MessageType::Error);
	}
}

///Checks if the specific Texture is already loaded in.
///filePath: The filepath to the Texture.
bool ResourceManager::TextureLoadedIn(std::string filePath)
{
	bool loadedIn = false;
	std::map<std::string, Texture*>::iterator it;
	for(it = _textures.begin(); it != _textures.end(); it++)
	{
		if(it->second != NULL)
		{
			if(it->second->GetFilePath().compare(filePath) == 0)
			{
				loadedIn = true;
				break;
			}
		}
	}
	return loadedIn;
}

///Gives the name of the loaded in Texture.
///filePath: The filepath to the loaded in Texture.
std::string ResourceManager::GetTextureName(std::string filePath)
{
	std::map<std::string, Texture*>::iterator it;
	for(it = _textures.begin(); it != _textures.end(); it++)
	{
		if(it->second != NULL)
		{
			if(it->second->GetFilePath().compare(filePath) == 0)
			{
				return it->first;
			}
		}
	}
}