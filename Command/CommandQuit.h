#pragma once
#include "Command.h"

namespace Commands
{
	class CommandQuit : public Command
	{
		const std::string name = "quit";
		const std::string desc = "Quits program.";
	public:
		void execute(CmdVec&);
		std::string getDesc() { return desc; }
		std::string getName() { return name; }
	};
}
