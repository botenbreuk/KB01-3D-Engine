#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <iostream>

class Resource
{
public:
	virtual ~Resource(void);
	std::string GetFilePath();

private:
	
protected:
	std::string _filePath;
	void SetFilePath(std::string filePath);
};

#endif