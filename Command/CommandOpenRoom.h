#pragma once
#include "Command.h"

namespace Commands
{
	class CommandOpenRoom : public Command
	{
		const std::string name = "openroom";
		const std::string desc = "Opens a room for people to connect to.";
	public:
		void execute(CmdVec&);
		std::string getDesc() { return desc; }
		std::string getName() { return name; }
	};
}
