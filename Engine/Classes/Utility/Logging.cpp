#include "Logging.h"
#include <chrono>
#include "fmt/chrono.h"

#define Entry_LogType(Name, Idx) #Name ,
static std::string LOG_TYPE_NAMES[LogMAX] =
{
	Entries_LogType
};
#undef Entry_LogType

std::vector<std::vector<LogEntry>> Log::LogEntries = std::vector<std::vector<LogEntry>>(LogMAX);

void Log::Write(const LogType Type, const std::string& LogText)
{
	LogEntries[Type].emplace_back(LogText);

	Log::PrintLog(Type, LogText, uint64(-1));
}

void Log::Read(const LogTypeFlags Type /*= flLogALL*/)
{
	const std::string _Divider = "==================================================================";
	Type; /** @note(devlinw): Eventually we will support log sorting */
	
	if (Type == FlLogALL)
	for (uint32 i = 0; i < LogEntries.size(); ++i)
	{
		if (!LogEntries.at(i).empty())
		{
			for (const LogEntry& Entry : LogEntries[i])
			{
				std::cout << _Divider << std::endl;
				PrintLog(LogType(i), Entry.Message, Entry.Timestamp);
			}

			std::cout << std::endl;
		}
	}
	else
	{
		for (int C = 0; C < LogMAX; ++C)
		{
			if ((Type & ToLogFlag(LogType(C))) != 0)
			{
				for (const LogEntry& Entry : LogEntries[C])
				{
					std::cout << _Divider << std::endl;
					PrintLog(LogType(C), Entry.Message, Entry.Timestamp);
				}

				std::cout << std::endl;
			}
		}
	}
}

void Log::Clear()
{
	for (auto& It : LogEntries)
	{
		It.clear();
	}
}

using namespace std::chrono;

void Log::PrintLog(const LogType Type, const std::string& LogText, uint64 Timestamp)
{
	if (Timestamp == uint64(-1)) Timestamp = system_clock::now().time_since_epoch().count();

	#pragma warning(push)
	#pragma warning(disable:4127)
	std::cout << fmt::format("({:%H:%M:%S}) [{}]: {}\n", system_clock::duration(Timestamp), LOG_TYPE_NAMES[Type], LogText);
	#pragma warning(pop)
}


LogEntry::LogEntry(const std::string& _Message) : Message(_Message), Timestamp(system_clock::now().time_since_epoch().count())
{
	
}
