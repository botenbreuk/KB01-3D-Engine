#include <iostream>
#include <time.h>

class Log
{
public:
	Log(void);
	~Log(void);
	enum MessageType {Error, Warning, Info};//The different types of messages the log knows and uses.
	const char* MtToChar(MessageType mt);//Converts the value of the MessageType mt to char*.
	void WriteLog(const char* logMessage, MessageType mt);//Method to write message to log
};


