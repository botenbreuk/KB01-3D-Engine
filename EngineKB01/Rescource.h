#pragma once
#include <string>

class Rescource
{
public:
	virtual ~Rescource(void);
	std::string GetFilePath();

private:
	
protected:
	std::string FilePath;
	void SetFilePath(std::string filePath);
};

