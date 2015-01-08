#include "LoggerPool.h"

LoggerPool* LoggerPool::_instance = NULL;//Define the singleton instance

LoggerPool::LoggerPool()
{
	_available = new std::list<Logger*>();
	_inUse = new std::list<Logger*>();
}

///Returns the singleton instance of this class
LoggerPool* LoggerPool::GetInstance()
{
	if(NULL == _instance)
	{
		_instance = new LoggerPool();
	}
	return _instance;
}

///Returns an available logger, or if there are none,
///creates a new logger and returns that instead
Logger* LoggerPool::GetLogger()
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

///Puts a logger that was in use back into the available loggers
void LoggerPool::ReleaseLogger(Logger* l)
{
	//TODO: let the logger forget to which logfile it needs to write
	_available->push_back(l);
	_inUse->remove(l);
}