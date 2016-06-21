#pragma once
#include "Command.h"

namespace Commands
{
	class CommandHelp : public Command
	{
		const std::string name = "help";
		const std::string desc = "Lists commands and descriptions.";
	public:
		void execute(CmdVec&);
		std::string getDesc() { return desc; }
		std::string getName() { return name; }
	};
}
