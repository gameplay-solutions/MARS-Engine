#include "Logging.h"

static std::string LOG_TYPE_NAMES[] =
{
	"LogTemp",
	"LogWarning",
	"LogError",
	"LogInit",
};

int32 NumLogTypes = LogGraphics - LogTemp + 1;
std::vector<std::vector<std::string>> Log::LogEntries = std::vector<std::vector<std::string>>(NumLogTypes);

void Log::Write(const LogType Type, const std::string& LogText)
{
	LogEntries[Type].push_back(LogText);

	Log::PrintLog(Type, LogText);
}

void Log::Read(const LogType Type /*= LogTemp*/)
{
	const std::string _Divider = "==================================================================";
	Type; /** @NOTE(Chrisr): Eventually we will support log sorting */
	
	for (uint32 i = 0; i < LogEntries.size(); ++i)
	{
		if (!LogEntries.at(i).empty())
		{
			for (uint32 j = 0; j < LogEntries.at(i).size(); ++j)
			{
				std::cout << _Divider << std::endl;
				std::cout << std::setw(7) << LOG_TYPE_NAMES[i] << ": " << LogEntries.at(i).at(j) << std::endl;
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
}

void Log::PrintLog(const LogType Type, const std::string& LogText)
{
	std::string _TypeName;
	
	switch (Type)
	{
		case LogWarning:
		{
			_TypeName = "LogWarning";
		} break;

		case LogError:
		{
			_TypeName = "LogError";
		} break;

		case LogInit:
		{
			_TypeName = "LogInit";
		} break;

		case LogGraphics:
		{
			_TypeName = "LogGraphics";
		} break;
		
		default:
		{
			_TypeName = "LogTemp";
		} break;
	}

	std::cout << std::setw(7) << _TypeName << ": " << LogText << std::endl;
}
