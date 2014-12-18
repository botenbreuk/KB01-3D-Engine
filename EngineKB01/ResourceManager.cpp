#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
}

/*
Converts a string to a char* for the Log.
String: The string to be converted.
*/
char* ResourceManager::StringToChar(std::string convertString)
{
	char* returnChar = new char[convertString.size() + 1];
	std::copy(convertString.begin(), convertString.end(), returnChar);
	returnChar[convertString.size()] = '\0';

	return returnChar;
}