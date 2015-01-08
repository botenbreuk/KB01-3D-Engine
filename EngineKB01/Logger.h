#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <iostream>
#include <time.h>
#include <string>

class Logger
{
public:
	Logger();
	~Logger();
	enum MessageType {Error, Warning, Info};//The different types of messages the log knows and uses.
	void WriteLog(const char* logMessage, MessageType mt);//
	void WriteLog(std::string logMessage, MessageType mt);//Methods to write message to log

private:
	const char* MtToChar(MessageType mt);//Converts the value of the MessageType mt to char*.
};

#endif