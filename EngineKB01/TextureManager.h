#pragma once
#include "RescourceManager.h"

class TextureManager : RescourceManager
{
public:
	TextureManager(Log* logger);
	~TextureManager(void);
	Texture* GetTexture(std::string textureName);//Returns a pointer to the texture with the given name.
	void AddTexture(std::string textureName, std::string filePath);//Loads in a texture.

private:
	std::map<std::string, Texture*> Textures;//A Key Value pair list of textures with the associated names.
};