#pragma once
#include "Rescource.h"
#include "Texture.h"
#include <map>
#include <utility>
#include "Mesh.h"
#include "Log.h"
#include <string>

class RescourceManager
{
public:;
	~RescourceManager(void);

protected:
	Log* Logger;//
	char* StringToChar(std::string String);//Converts a string to a char* for the Log.
};