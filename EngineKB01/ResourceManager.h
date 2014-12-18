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

protected:
	Log* Logger;//
	char* StringToChar(std::string String);//Converts a string to a char* for the Log.
};

#endif