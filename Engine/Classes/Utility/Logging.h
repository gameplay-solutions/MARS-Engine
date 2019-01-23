#pragma once

#include "Core/EngineCore.h"
#include "fmt/format.h"

enum LogType
{
	LogTemp = 0,
	LogWarning = 2,
	LogError = 4,
	LogInit = 8,
	LogGraphics = 16,
};

class Log
{
	/** 
	 * @note(devlinw): chris says "Using vectors instead of maps here because it will force everything to be linear in memory
	 * I.E, looping over a log is more cache efficient this way than with a map"
	 **/

	static std::vector<std::vector<std::string>> LogEntries;

public:

	/**
	 *	Writes a single log with a specified LogType. All logs are placed in a queue
	 **/
	static void Write(const LogType Type, const std::string& LogText);
	
	/**
	 *	Writes a single log with a specified LogType, and allows variadic arguments. All logs are placed in a queue
	 **/
	template<class ... T>
	static void Write(const LogType Type, const std::string& LogText, T...Args)
	{
		Write(Type, fmt::format(LogText, Args...));
	}

	/** 
	 *	Reads all logs for a specific LogType. It will read all temp logs by default, this can be changed by the caller.
	 **/
	static void Read(const LogType Type = LogTemp);

	static void Clear();

	/** @NOTE(Chrisr): Possible Log IO? */

private:

	static void PrintLog(const LogType Type, const std::string& LogText);

};