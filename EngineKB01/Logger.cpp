#include "Logger.h"

Logger::Logger(std::string logFileName)
{
	_logFileName = logFileName;
}

///Method to write message to log
///logMessage: the message,
///mt: MessageType enum
///File /EngineKB01/LogFile.txt is created automatically (if it does not exist yet)
void Logger::WriteLog(const char* logMessage, MessageType mt)
{
	//Code to get time of logging
	time_t timer = time(NULL);
	tm* ptm = localtime(&timer);
	char currentTimeDate[40];
	strftime(currentTimeDate, 32, "%d.%m.%Y %H:%M:%S", ptm);

	//Converts the specific message type to characters so they can be written in the logfile
	const char* messType = MtToChar(mt);

	//initializes the complete logmessage
	std::string fullMessage = currentTimeDate;
	fullMessage += " - ";
	fullMessage += messType;
	fullMessage += ": ";
	fullMessage += logMessage;

	//Create log folder if not exists.
	struct stat info;
	if (stat("/some/directory", &info) == -1)
		CreateDirectory(L"Logs", NULL);

	//Initializes the filepath to write to
	std::string filePath = "Logs/";
	filePath += _logFileName;
	filePath += ".txt";

	//Writes the message to the logfile
	FILE* pFile = fopen(filePath.c_str(), "a");
	fprintf(pFile, fullMessage.c_str());
	fprintf(pFile, "\n");
	fclose(pFile);

	//Writes the same message to the console
	std::cout << fullMessage << std::endl;
}

///Method to write message to log using a string
///calls WriteLog(const char* logMessage, MessageType mt)
///logMessage: the message,
///mt: MessageType enum
///File /EngineKB01/LogFile.txt is created automatically (if it does not exist yet)
void Logger::WriteLog(std::string logMessage, MessageType mt)
{
	const char* logMessageInChar = StringToChar(logMessage);
	WriteLog(logMessageInChar, mt);
}

void Logger::setWriteDestination(std::string logFileName)
{
	_logFileName = logFileName;
}

const char* Logger::StringToChar(std::string s)
{
	char* returnChar = new char[s.size() + 1];
	std::copy(s.begin(), s.end(), returnChar);
	returnChar[s.size()] = '\0';

	return returnChar;
}

///Convert value of enum to char*
///mt: Specific MessageType to be converted.
const char* Logger::MtToChar(MessageType mt)
{
	//Initialises the returnPointer to the errormessage of not having found the correct way to translage mt
	char* returnPointer = "Failed to translate messagetype to Char* ";

	//Checks the existing MessageTypes and changes returnPointer accordingly
	//If no correct translation can be found, the returnpointer will remain set to the errormessage
	switch (mt)
	{
		case Error:		returnPointer = "Error";
			break;
		case Warning:	returnPointer = "Warning";
			break;
		case Info:		returnPointer = "Info";
			break;
	}

	//Returns the returnPointer
	return returnPointer;
}

Logger::~Logger()
{
}