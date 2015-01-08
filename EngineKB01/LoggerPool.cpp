#include "LoggerPool.h"

LoggerPool::LoggerPool()
{
	_available = new std::list<Logger*>();
	_inUse = new std::list<Logger*>();

}

Logger* LoggerPool::getLogger()
{
	if(0 <_available->size())
	{
		Logger* l = _available->front();
		_inUse->push_back(l);
		_available->pop_front();
		return l;
	}
	else
	{
		Logger* l = new Logger();
		_inUse->push_back(l);
		return l;
	}
}

void LoggerPool::releaseLogger(Logger* l)
{
	_available->push_back(l);
	_inUse->remove(l);
}