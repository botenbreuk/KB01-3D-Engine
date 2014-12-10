#pragma once
#include "Renderer.h"
#include "Log.h"

class Kernel
{
public:
	Kernel(void);
	~Kernel(void);

private:
	Renderer* Renderer;
	Log* Logger;
	void TestLog();//Testcode for the Log
	void TestRescourceManagers();//Testcode for the RescourceManagers.
};