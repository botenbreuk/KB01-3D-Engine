#ifndef __LOG_H__
#define __LOG_H__

#include <iostream>
#include <time.h>

class Log
{
public:
	Log();
	~Log();
	enum MessageType {Error, Warning, Info};//The different types of messages the log knows and uses.
	void WriteLog(const char* logMessage, MessageType mt);//Method to write message to log

private:
	const char* MtToChar(MessageType mt);//Converts the value of the MessageType mt to char*.
};

#endif