#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__
#include "ResourceManager.h"

class TextureManager : ResourceManager
{
public:
	TextureManager(Log* logger);
	~TextureManager();
	Texture* GetTexture(std::string textureName);//Returns a pointer to the Texture with the given name.
	void LoadTexture(std::string textureName, std::string filePath);//Loads in a Texture.

private:
	std::map<std::string, Texture*> Textures;//A Key Value pair list of textures with the associated names.
	bool TextureLoadedIn(std::string filePath);//Checks if the specific Texture is already loaded in.
	std::string GetTextureName(std::string filePath);//Gives the name of the loaded in Texture.
};

#endif