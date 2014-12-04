#pragma once
#include "Renderer.h"
#include "Log.h"

class Kernel
{
public:
	Kernel(void);
	~Kernel(void);
	static int main();
	void TestLog();

private:
	Renderer* Renderer;
	Log* Logger;
};