#ifndef _LOGGERPOOL_H_
#define _LOGGERPOOL_H_

#include <list>

#include "Logger.h"

class LoggerPool
{
public:
	static LoggerPool* GetInstance(); //Returns the singleton instance of this class
	Logger* GetLogger(std::string logFileName);
	void ReleaseLogger(Logger* logger);
private:
	static LoggerPool* _instance;//The singleton instance of this class
	LoggerPool();
	LoggerPool(LoggerPool const&);	  //These constructors are also private, so that
	void operator=(LoggerPool const&);//the singleton instance cannot be copied
	std::list<Logger*>* _available;//The list of available loggers
	std::list<Logger*>* _inUse;//The list of loggars that are currently in use
};

#endif