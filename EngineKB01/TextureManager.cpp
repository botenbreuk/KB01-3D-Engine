#include "TextureManager.h"


TextureManager::TextureManager(void)
{
}


TextureManager::~TextureManager(void)
{
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
	if(NULL == Textures[textureName])
	{
		Texture* t = new Texture(filePath);
		Textures[textureName] = t;
	}
}