#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <iostream>
#include <time.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <Windows.h>

class Logger
{
public:
	Logger(std::string logFileName);
	~Logger();
	enum MessageType {Error, Warning, Info};//The different types of messages the log knows and uses.
	void WriteLog(const char* logMessage, MessageType mt);//
	void WriteLog(std::string logMessage, MessageType mt);//Methods to write message to log.
	void setWriteDestination(std::string logFileName);//Tells the logger where to which file to write to
private:
	std::string _logFileName;//The name of file to write to.
	const char* StringToChar(std::string s);//Converts the value of String s to char*.
	const char* MtToChar(MessageType mt);//Converts the value of MessageType mt to char*.
};

#endif