#include "Logger.h"

Logger::Logger()
{
}


///Method to write message to log.
///logMessage: the message,
///mt: MessageType enum.
///File /EngineKB01/LogFile.txt is created automatically (if it does not exist yet).
void Logger::WriteLog(const char* logMessage, MessageType mt)
{
	//Code to get time of logging.
	time_t timer = time(NULL);
	tm* ptm = localtime(&timer);
	char currentTimeDate[40];
	strftime(currentTimeDate, 32, "%d.%m.%Y %H:%M:%S", ptm);

	//Converts the specific message type to characters so they can be written in the logfile
	const char* messType = MtToChar(mt);

	//Writes to the logfile.
	FILE* pFile = fopen("LogFile.txt", "a");
	fprintf(pFile, currentTimeDate);
	fprintf(pFile, " - ");
	fprintf(pFile, messType);
	fprintf(pFile, ": ");
	fprintf(pFile, logMessage);
	fprintf(pFile, "\n");
	fclose(pFile);
}

///Method to write message to log using a string.
///calls WriteLog(const char* logMessage, MessageType mt).
///logMessage: the message,
///mt: MessageType enum.
///File /EngineKB01/LogFile.txt is created automatically (if it does not exist yet).
void Logger::WriteLog(std::string logMessage, MessageType mt)
{
	char* returnChar = new char[logMessage.size() + 1];
	std::copy(logMessage.begin(), logMessage.end(), returnChar);
	returnChar[logMessage.size()] = '\0';

	WriteLog(returnChar, mt);
}

///Convert value of enum to char*
///mt: Specific MessageType to be converted.
const char* Logger::MtToChar(MessageType mt)
{
	//Initialises the returnPointer to the errormessage of not having found the correct way to translage mt;
	char* returnPointer = "Failed to translate messagetype to Char* ";

	//Checks the existing MessageTypes and changes returnPointer accordingly. If no correct translation can be found, the returnpointer will remain set to the errormessage.
	switch (mt)
	{
		case Error:		returnPointer = "Error";
			break;
		case Warning:	returnPointer = "Warning";
			break;
		case Info:		returnPointer = "Info";
			break;
	}

	//Returns the returnPointer.
	return returnPointer;
}

Logger::~Logger()
{
}