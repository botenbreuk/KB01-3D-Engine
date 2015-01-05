#include "MeshManager.h"

MeshManager::MeshManager()
{
	Mesh* dummy = new Mesh("tiger.x");
	Meshes["tiger.x"] = dummy;
}

MeshManager::MeshManager(Log* logger, DirectXRenderer* renderer)
{
	Logger = logger;
	Renderer = renderer;
	Mesh* dummy = new Mesh("tiger.x");
	Meshes["tiger.x"] = dummy;
}

/*
Loads in the Meshes.
*/
void MeshManager::LoadMeshes(){

	std::list<Mesh*> meshList;

	std::map<std::string, Mesh*>::const_iterator iter;
	for(iter = Meshes.begin(); iter != Meshes.end(); iter++)
	{
		meshList.push_front(iter->second);
	}

	Renderer->InitGeometry(meshList);
}

MeshManager::~MeshManager()
{
	delete Logger;
}

/*
Returns a pointer to the Mesh with the given name.
meshName: The name of the Mesh to be returned.
*/
Mesh* MeshManager::GetMesh(std::string meshName)
{
	return Meshes[meshName];
}

/*
Loads in a Mesh.
meshName: The Key name of the Mesh.
filePath: The filepath to the Mesh.
*/
void MeshManager::LoadMesh(std::string meshName, std::string filePath)
{
	//Initialises several strings that can be sent to the log.
	std::string succesString = "Mesh: '" + meshName + "' loaded in as '" + filePath + "'.";//Gets in the log if the Mesh is loaded in without any problems.
	std::string failString1 = "A Mesh with the name: '" + meshName + "' already exists.";//Gets in the log if that Key value is already taken in the list.
	std::string failString2 = "That Mesh is already loaded in with the name: '";//Gets in the log if that Mesh is already loaded in.

	//Initialises the char* that will be written to the log.
	char* message;

	if(NULL == Meshes[meshName])//Checks if there is alreay a Mesh with that name.
	{
		if(!MeshLoadedIn(filePath))//Checks if the specific Mesh is already loaded in.
		{
			//Loads in the Mesh.
			Mesh* m = new Mesh(filePath);
			Meshes[meshName] = m;
			
			//Converts succesString to a Char* and writes it to the log.
			Logger->WriteLog(succesString, Log::MessageType::Info);
		}
		else
		{
			//Texture already loaded in
			Logger->WriteLog(failString2 + " " + GetMeshName(filePath) + "'.", Log::MessageType::Error);
		}

	}
	else
	{
		//texture already loaded with that name
		Logger->WriteLog(failString1, Log::MessageType::Error);
	}
}

/*
Checks if the specific Mesh is already loaded in.
filePath: The filepath to the Mesh.
*/
bool MeshManager::MeshLoadedIn(std::string filePath)
{
	bool loadedIn = false;
	std::map<std::string, Mesh*>::iterator it;
	for(it = Meshes.begin(); it != Meshes.end(); it++)
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

/*
Gives the name of the loaded in Mesh.
filePath: The filepath to the loaded in Mesh.
*/
std::string MeshManager::GetMeshName(std::string filePath)
{
	std::map<std::string, Mesh*>::iterator it;
	for(it = Meshes.begin(); it != Meshes.end(); it++)
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