#ifndef __WINDOWSCENECONNECTOR_H__
#define __WINDOWSCENECONNECTOR_H__

#include <list>
#include <map>
#include "Scene.h"
#include "Window.h"

class WindowSceneConnector
{
public:
	WindowSceneConnector();
	~WindowSceneConnector();
	std::list<std::pair<Scene*, Window*>> GetList();
	void AddConnection(Scene* scene, Window* window);

private:
	std::list<std::pair<Scene*, Window*>> _pairs;
};

#endif