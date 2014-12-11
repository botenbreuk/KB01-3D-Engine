#include "TextureManager.h"


TextureManager::TextureManager(Log* logger)
{
	Logger = logger;
}


TextureManager::~TextureManager(void)
{
	delete Logger;
}

/*
Returns a pointer to the texture with the given name.
textureName: The name of the texture to be returned.
*/
Texture* TextureManager::GetTexture(std::string textureName)
{
	return Textures[textureName];
}

/*
Loads in a texture.
textureName: The Key name of the texture.
filePath: The filepath to the textrue.
*/
void TextureManager::AddTexture(std::string textureName, std::string filePath)
{
	//Initialises several strings that can be sent to the log.
	std::string succesString = "Texture: " + textureName + " loaded in as " + filePath + ".";//Gets in the log if the Texture is loaded in without any problems.
	std::string failString1 = "A Texture with the name: " + textureName + " already exists.";//Gets in the log if that Key value is already taken in the list.
	std::string failString2 = "That Texture is already loaded in with the name: ";//Gets in the log if that Texture is already loaded in.

	//Initialises the char* that will be written to the log.
	char* message;

	if(NULL == Textures[textureName])//Checks if there is alreay a Texture with that name.
	{
		if(!TextureLoadedIn(filePath))//Checks if the specific Texture is already loaded in.
		{
			//Loads in the Texture.
			Texture* t = new Texture(filePath);
			Textures[textureName] = t;

			//Converts succesString to a Char* and writes it to the log.
			message = StringToChar(succesString);
			Logger->WriteLog(message, Log::MessageType::Info);
		}
		else
		{
			//Converts failString2 to a Char* and writes it to the log.
			message = strcat(StringToChar(failString2), StringToChar(GetTextureName(filePath)));
			Logger->WriteLog(message, Log::MessageType::Error);
		}

	}
	else
	{
		//Converts failString1 to a Char* and writes it to the log.
		message = StringToChar(failString1);
		Logger->WriteLog(message, Log::MessageType::Error);
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