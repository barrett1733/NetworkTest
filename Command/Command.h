#pragma once
#include <string>
#include <vector>
#include "../Options.h"

namespace Commands
{
	typedef std::vector<std::string> CmdVec;

	class Command : public OptionsHandler
	{
	public:
		virtual void execute(CmdVec&) = 0;
		virtual std::string getDesc() = 0;
		virtual std::string getName() = 0;
	};

	// First string is always command.
	// Will never return an empty CmdVec.
	CmdVec parseCommand(std::string);
}