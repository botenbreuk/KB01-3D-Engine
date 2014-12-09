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
	void TestLog();
	void TestRescourceManager();
};