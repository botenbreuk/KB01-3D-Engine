#pragma once
#include <string>

class Rescource
{
public:
	virtual ~Rescource(void);
	std::string GetFilepath();

private:
	
protected:
	std::string filePath;
	void SetFilePath(std::string filePath);
};

