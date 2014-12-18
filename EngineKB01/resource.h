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
	std::string FilePath;
	void SetFilePath(std::string filePath);
};

#endif