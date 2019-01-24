#pragma once

#include "Core/EngineCore.h"
#include "fmt/format.h"

// #define Entry_LogType(Name, Idx)

#define Entries_LogType			\
Entry_LogType(LogTemp, 0)		\
Entry_LogType(LogWarning, 1)	\
Entry_LogType(LogError, 2)		\
Entry_LogType(LogInit, 3)		\
Entry_LogType(LogGraphics, 4)

#define Entry_LogType(Name, Idx) Fl##Name = (1 << Idx),
enum LogTypeFlags
{
	Entries_LogType

#undef Entry_LogType
#define Entry_LogType(Name, Idx) Fl##Name |

	FlLogALL = Entries_LogType /*|*/ 0,
};
#undef Entry_LogType
#define Entry_LogType(Name, Idx) Name = Idx,
enum LogType
{
	Entries_LogType
	LogMAX
};
#undef Entry_LogType

constexpr LogType FromLogFlag(LogTypeFlags Flags) 
{ 
	switch (Flags)
	{
#define Entry_LogType(Name, Idx) case Fl##Name: return Name;
		default: /** @todo(devlinw): Error */
		case FlLogALL: return LogMAX;
#undef Entry_LogType
	}
}

constexpr LogTypeFlags ToLogFlag(LogType Type) { return LogTypeFlags(1 << Type); }

__forceinline LogTypeFlags operator|(const LogTypeFlags& LHS, const LogTypeFlags& RHS)
{
	return LogTypeFlags(uint64(LHS) | uint64(RHS));
}

struct LogEntry
{
	uint64	Timestamp;
	int8	Cat;
	std::string Message;

	LogEntry(const std::string& _Message, const LogType _Type);

	// only public for std::vector - do not use
	LogEntry() {}
};

class Log
{
	/** 
	 * @note(devlinw): chris says "Using vectors instead of maps here because it will force everything to be linear in memory
	 * I.E, looping over a log is more cache efficient this way than with a map"
	 **/

	/** @todo(devlinw): best gains here likely from custom alloc - bucket for each cat, fixed size for outer container? */
	static std::vector<std::vector<LogEntry>>	LogEntries;

	/** @note(devlinw): conscious decision to double mem footprint to optimize case of dumping a full, sorted log.  */
	static std::vector<LogEntry>				AllLogEntries; 

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
	 *	
	 *	@param CombineAll Whether all the logs should be collated into the same sorted list.
	 **/
	static void Read(const LogTypeFlags Type = FlLogALL, bool CombineAll = true);

	static void Clear();

	/** @note(devlinw): chris thinks logging to a file might be cool */

private:

	static void PrintLog(const LogType Type, const std::string& LogText, uint64 Timestamp);

};