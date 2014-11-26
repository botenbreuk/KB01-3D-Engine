#include <iostream>
#include <string>
#include <time.h> 

class Log
{
public:
	Log(void);
	~Log(void);
	enum MessageType {Error, Warning, Info};
	const char* MtToChar(MessageType mt);
	
	//Method to write message to log
	void WriteLog(const char* logMessage, MessageType mt);
};


