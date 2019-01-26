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

/// Color is from fmt::color
/// TECHNICALLY, we can support either/or fmt::color and fmt::terminal_color. However, MS's cmd.exe appears to work just fine with the full color, so meh.
/// We could ALSO have this be a full on hex code but at THIS time I'm not supporting it.
// #define Entry_LogImportance(Name, Idx, Color)

#define Entries_LogImportance \
Entry_LogImportance(LI_Ancillary, 0, gray) \
Entry_LogImportance(LI_Info, 1, white) \
Entry_LogImportance(LI_Warning, 2, pale_golden_rod) \
Entry_LogImportance(LI_Error, 3, tomato) \
Entry_LogImportance(LI_Fatal, 4, red)

#define Entry_LogImportance(Name, Idx, Color) Name = Idx,
enum LogImportance
{
	Entries_LogImportance
	LI_Max,
};
#undef Entry_LogImportance

struct LogEntry
{
	uint64			Timestamp;
	int8			Cat;
	LogImportance	Importance;
	std::string		Message;

	LogEntry(const std::string& _Message, const LogType _Type, const LogImportance _Importance = LI_Info);

	// only public for std::vector - do not use
	LogEntry() {}
};

class CategoricLog
{
	LogType Type;

public:

	/**
	 *	Writes a single unformatted message to the log as Importance.
	 **/
	void Write(const std::string& LogText, const LogImportance Importance = LI_Info);
	
	/**
	 *	Writes a single formatted message to the log as Info, and allows variadic arguments.
	 **/
	template<class ... T>
	void Write(const std::string& LogText, T...Args)
	{
		Write(fmt::format(LogText, Args...), LI_Info);
	}

	/**
	 *	Writes a single formatted message to the log as specified Importance, and allows variadic arguments.
	 **/
	template<class ... T>
	void Importance(const LogImportance Importance, const std::string& LogText, T...Args)
	{
		Write(fmt::format(LogText, Args...), Importance);
	}
	
	/**
	 *	Writes a single formatted message to the log as Ancillary, and allows variadic arguments.
	 **/
	template<class ... T>
	void Ancillary(const std::string& LogText, T...Args)
	{
		Write(fmt::format(LogText, Args...), LI_Ancillary);
	}

	/**
	 *	Writes a single formatted message to the log as Info, and allows variadic arguments.
	 **/
	template<class ... T>
	void Info(const std::string& LogText, T...Args)
	{
		Write(fmt::format(LogText, Args...), LI_Info);
	}

	/**
	 *	Writes a single formatted message to the log as Warning, and allows variadic arguments.
	 **/
	template<class ... T>
	void Warning(const std::string& LogText, T...Args)
	{
		Write(fmt::format(LogText, Args...), LI_Warning);
	}

	/**
	 *	Writes a single formatted message to the log as Error, and allows variadic arguments.
	 **/
	template<class ... T>
	void Error(const std::string& LogText, T...Args)
	{
		Write(fmt::format(LogText, Args...), LI_Error);
	}

	/**
	 *	Writes a single formatted message to the log as Fatal, and allows variadic arguments.
	 **/
	template<class ... T>
	void Fatal(const std::string& LogText, T...Args)
	{
		Write(fmt::format(LogText, Args...), LI_Fatal);
	}

	/** 
	 *	Reads the log for the specified category.
	 **/
	void Read();

	// do not use, public for map only.
	CategoricLog() : Type(LogMAX) {}
	// do not use, public for map only.
	CategoricLog(CategoricLog&&) = default;
	// do not use, public for map only.
	CategoricLog& operator=(CategoricLog&&) = default;

	/** @note(devlinw): Can only take a ref to this type. */
	CategoricLog(const CategoricLog&) = delete;
	CategoricLog& operator=(const CategoricLog&) = delete;

private:

	CategoricLog(LogType _Type) : Type(_Type) {}

	friend class Log;
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

	/** @todo(devlinw): return reference to locally kept objects #CategoricTidy */
	static CategoricLog& Get(const LogType Type);

	/**
	 *	Writes a single log with a specified LogType. All logs are placed in a queue
	 **/
	static void Write(const LogImportance Importance, const LogType Type, const std::string& LogText);
	
	/**
	 *	Writes a single log with a specified LogType, and allows variadic arguments. All logs are placed in a queue
	 **/
	template<class ... T>
	static void Write(const LogImportance Importance, const LogType Type, const std::string& LogText, T...Args)
{
		Write(Importance, Type, fmt::format(LogText, Args...));
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

	static void PrintLog(const LogEntry& Log);
	static void PrintLog(const LogType Type, const std::string& LogText, uint64 Timestamp, const LogImportance Importance = LI_Info);
};