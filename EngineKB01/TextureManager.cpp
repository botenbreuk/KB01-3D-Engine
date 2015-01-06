#include "TextureManager.h"


TextureManager::TextureManager(Log* logger)
{
	Logger = logger;
}


TextureManager::~TextureManager()
{
	delete Logger;
}

/*
Returns a pointer to the Texture with the given name.
textureName: The name of the Texture to be returned.
*/
Texture* TextureManager::GetTexture(std::string textureName)
{
	return Textures[textureName];
}

/*
Loads in a Texture.
textureName: The Key name of the Texture.
filePath: The filepath to the Textrue.
*/
void TextureManager::LoadTexture(std::string textureName, std::string filePath)
{
	//Initialises several strings that can be sent to the log.

	//Gets in the log if the Texture is loaded in without any problems.
	std::string succesString = "Texture: '" + textureName + "' loaded in as '" + filePath + "'.";
	//Gets in the log if that Key value is already taken in the list.
	std::string failString1 = "A Texture with the name: '" + textureName + "' already exists.";
	//Gets in the log if that Texture is already loaded in.
	std::string failString2 = "That Texture is already loaded in with the name: '";

	//Initialises the char* that will be written to the log.
	char* message;

	//Checks if there isn't a Texture with that name already.
	if(NULL == Textures[textureName])
	{
		//Checks if the specific Texture is already loaded in.
		if(!TextureLoadedIn(filePath))
		{
			//Loads in the Texture.
			Texture* t = new Texture(filePath);
			Textures[textureName] = t;

			//Converts succesString to a Char* and writes it to the log.
			Logger->WriteLog(succesString, Log::MessageType::Info);
		}
		else
		{
			//Texture already loaded in
			Logger->WriteLog(failString2 + " " + GetTextureName(filePath) + "'.", Log::MessageType::Error);
		}

	}
	else
	{
		//texture already loaded with that name
		Logger->WriteLog(failString1, Log::MessageType::Error);
	}
}

/*
Checks if the specific Texture is already loaded in.
filePath: The filepath to the Texture.
*/
bool TextureManager::TextureLoadedIn(std::string filePath)
{
	bool loadedIn = false;
	std::map<std::string, Texture*>::iterator it;
	for(it = Textures.begin(); it != Textures.end(); it++)
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
Gives the name of the loaded in Texture.
filePath: The filepath to the loaded in Texture.
*/
std::string TextureManager::GetTextureName(std::string filePath)
{
	std::map<std::string, Texture*>::iterator it;
	for(it = Textures.begin(); it != Textures.end(); it++)
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