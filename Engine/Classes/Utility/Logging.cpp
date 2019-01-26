#include "Logging.h"
#include <chrono>
#include "fmt/chrono.h"
#include "fmt/color.h"
#include <map>

#define Entry_LogType(Name, Idx) #Name ,
static std::string LOG_TYPE_NAMES[LogMAX] =
{
	Entries_LogType
};
#undef Entry_LogType

#define Entry_LogImportance(Name, Idx, Color) #Name ,
static std::string LOG_IMPORTANCE_NAMES[LI_Max] =
{
	Entries_LogImportance
};
#undef Entry_LogImportance

#define Entry_LogImportance(Name, Idx, Color) fmt::color::##Color ,
static fmt::color LOG_IMPORTANCE_COLORS[LI_Max] = /* */
{
	Entries_LogImportance
};
#undef Entry_LogImportance

std::vector<std::vector<LogEntry>> Log::LogEntries = std::vector<std::vector<LogEntry>>(LogMAX);
std::vector<LogEntry> Log::AllLogEntries = std::vector<LogEntry>();

CategoricLog& Log::Get(const LogType Type)
{
	static std::map<LogType, CategoricLog> CategoricLogs;

	if (CategoricLogs.find(Type) == CategoricLogs.end())
	{
		CategoricLogs.emplace(Type, CategoricLog(Type));
	}

	return CategoricLogs[Type];
}

void Log::Write(const LogImportance Importance, const LogType Type, const std::string& LogText)
{
	LogEntries[Type].emplace_back(LogText, Type, Importance);
	AllLogEntries.emplace_back(LogText, Type, Importance);

	Log::PrintLog(Type, LogText, uint64(-1), Importance);
}

void Log::Read(const LogTypeFlags Type /*= FlLogALL*/, bool CombineAll /*= true*/)
{
	const std::string _Divider = "==================================================================";

	std::cout << _Divider << std::endl;
	if (Type == FlLogALL)
	{
		for (const LogEntry& Entry : AllLogEntries)
		{
			PrintLog(Entry);
		}
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
					PrintLog(Entry);
				}

				if (C != (LogMAX - 1)) std::cout << _Divider << std::endl;
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
				PrintLog(Entry);
			}
		}
	}
	std::cout << _Divider << std::endl;
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

static void TerminalColorEscape(fmt::terminal_color DesiredColor, std::string& ColorEscapeCode)
{
	using namespace fmt::internal;
	auto EscCodeMaker = make_foreground_color<char>(color_type(DesiredColor));
	ColorEscapeCode.append(EscCodeMaker.begin());
}

static void TerminalColorEscape(fmt::color DesiredColor, std::string& ColorEscapeCode)
{
	using namespace fmt::internal;
	auto EscCodeMaker = make_foreground_color<char>(color_type(DesiredColor));
	ColorEscapeCode.append(EscCodeMaker.begin());
}

void Log::PrintLog(const LogType Type, const std::string& LogText, uint64 Timestamp, const LogImportance Importance /*= LI_Info*/)
{
	if (Timestamp == uint64(-1)) Timestamp = system_clock::now().time_since_epoch().count();

	/** @todo(devlinw): can we retrieve local hour or UTC offset easier than this? */
	tm TM;
	auto Dur = system_clock::duration(Timestamp);
	auto Point = system_clock::time_point(Dur);

	auto AT = system_clock::to_time_t(Point);
	localtime_s(&TM, &AT);

	std::string ColorEscapeCode;

	// bit annoying as I feel I should be able to insert a color in wherever I want by the normal method instead of doing anything like this.
	TerminalColorEscape(LOG_IMPORTANCE_COLORS[Importance], ColorEscapeCode);

	#pragma warning(push)
	#pragma warning(disable:4127)//constexpr if in library
	std::cout << fmt::format("({:0>2}:{:%M:%S}) [{}]:{} {} \x1b[0m\n", TM.tm_hour % 12, Dur, LOG_TYPE_NAMES[Type], ColorEscapeCode.c_str(), LogText);
	#pragma warning(pop)
}

void Log::PrintLog(const LogEntry& Log)
{
	PrintLog(LogType(Log.Cat), Log.Message, Log.Timestamp, Log.Importance);
}

LogEntry::LogEntry(const std::string& _Message, const LogType _Type, const LogImportance _Importance /*= LI_Info*/)
: Message(_Message)
, Timestamp(system_clock::now().time_since_epoch().count())
, Cat(decltype(Cat)(_Type))
, Importance(_Importance)
{}


void CategoricLog::Write(const std::string& LogText, const LogImportance Importance /*= LI_Info*/)
{
	Log::Write(Importance, Type, LogText);
}

void CategoricLog::Read()
{
	Log::Read(ToLogFlag(Type), false);
}