#ifndef _LOGGERPOOL_H_
#define _LOGGERPOOL_H_

#include <list>

#include "Logger.h"

static class LoggerPool
{
public:
	LoggerPool();
	~LoggerPool();
	static Logger* getLogger();
	static void releaseLogger(Logger* logger);
private:
	static std::list<Logger*>* _available;
	static std::list<Logger*>* _inUse;
};

#endif