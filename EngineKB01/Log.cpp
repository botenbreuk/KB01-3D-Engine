#include "Log.h"

Log::Log(void)
{
}

enum MessageType {Error, Warning, Info};

/*
Method to write message to log.
logMessage: the message,
mt: MessageType enum.
File /EngineKB01/LogFile.txt is created automatically (if it does not exist yet).
*/
void Log::WriteLog(const char* logMessage, MessageType mt)
{

	//Code to get time of logging.
	time_t timer = time(NULL);
	tm* ptm = localtime(&timer);
	char currentTimeDate[40];
	strftime(currentTimeDate, 32, "%d.%m.%Y %H:%M:%S", ptm);

	//Converts the specific message type to characters so they can be written in the logfile
	const char* messType = MtToChar(mt);

	//Writes the log message to a file.
    std::freopen("LogFile.txt", "a", stdout);
	std::printf(currentTimeDate);
	std::printf(" - ");
	std::printf(messType);
	std::printf(": ");
	std::printf(logMessage);
	std::printf("\n");
    std::fclose(stdout);
}

/*
Convert value of enum to char*
mt: Specific MessageType to be converted.
*/
const char* Log::MtToChar(MessageType mt)
{
	switch (mt)
    {
        case Error:		return "Error";
        case Warning:	return "Warning";
		case Info:		return "Info";
	}
}

Log::~Log(void)
{
}