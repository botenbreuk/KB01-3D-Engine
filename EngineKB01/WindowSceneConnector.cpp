#include "WindowSceneConnector.h"


WindowSceneConnector::WindowSceneConnector()
{
}


WindowSceneConnector::~WindowSceneConnector()
{
}

void WindowSceneConnector::AddConnection(Scene* scene, Window* window)
{
	std::pair<Scene*, Window*> pair;
	pair = std::make_pair(scene, window);
	_pairs.push_front(pair);
}

std::list<std::pair<Scene*, Window*>> WindowSceneConnector::GetList()
{
	return _pairs;
}