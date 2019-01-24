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
std::vector<LogEntry> Log::AllLogEntries = std::vector<LogEntry>();

void Log::Write(const LogType Type, const std::string& LogText)
{
	LogEntries[Type].emplace_back(LogText, Type);
	AllLogEntries.emplace_back(LogText, Type);

	Log::PrintLog(Type, LogText, uint64(-1));
}

void Log::Read(const LogTypeFlags Type /*= FlLogALL*/, bool CombineAll /*= true*/)
{
	const std::string _Divider = "==================================================================";
	
	if (Type == FlLogALL)
	{
		for (const LogEntry& Entry : AllLogEntries)
		{
			std::cout << _Divider << std::endl;
			PrintLog(LogType(Entry.Cat), Entry.Message, Entry.Timestamp);
		}

		std::cout << std::endl;
	}
	else
	{
		if (!CombineAll)
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
		else
		{
			std::vector<LogEntry> LocalEntries;

			for (int C = 0; C < LogMAX; ++C)
			{
				if ((Type & ToLogFlag(LogType(C))) != 0)
				{
					LocalEntries.insert(LocalEntries.end(), LogEntries[C].begin(), LogEntries[C].end());
				}
			}

			std::sort(LocalEntries.begin(), LocalEntries.end(), [](const LogEntry& LHS, const LogEntry& RHS){ return LHS.Timestamp < RHS.Timestamp; });

			for (const LogEntry& Entry : LocalEntries)
			{
				std::cout << _Divider << std::endl;
				PrintLog(LogType(Entry.Cat), Entry.Message, Entry.Timestamp);
			}

			std::cout << std::endl;
		}
	}
}

void Log::Clear()
{
	for (auto& It : LogEntries)
	{
		It.clear();
	}
	AllLogEntries.clear();
}

using namespace std::chrono;

void Log::PrintLog(const LogType Type, const std::string& LogText, uint64 Timestamp)
{
	if (Timestamp == uint64(-1)) Timestamp = system_clock::now().time_since_epoch().count();

	/** @todo(devlinw): can we retrieve local hour or UTC offset easier than this? */
	tm TM;
	auto Dur = system_clock::duration(Timestamp);
	auto Point = system_clock::time_point(Dur);

	auto AT = system_clock::to_time_t(Point);
	localtime_s(&TM, &AT);

	#pragma warning(push)
	#pragma warning(disable:4127)//constexpr if in library
	std::cout << fmt::format("({:0>2}:{:%M:%S}) [{}]: {}\n", TM.tm_hour % 12, Dur, LOG_TYPE_NAMES[Type], LogText);
	#pragma warning(pop)
}


LogEntry::LogEntry(const std::string& _Message, const LogType _Type) : Message(_Message), Timestamp(system_clock::now().time_since_epoch().count()), Cat(decltype(Cat)(_Type))
{
	
}
