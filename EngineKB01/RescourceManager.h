#pragma once
#include <vector>
#include "Rescource.h"
#include "Texture.h"

class RescourceManager
{
public:
	RescourceManager(void);
	~RescourceManager(void);
	
private:
	std::vector<Texture> textures;
};

