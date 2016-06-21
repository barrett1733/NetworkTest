#pragma once
#include "Command.h"

namespace Commands
{
	class CommandLeave : public Command
	{
		const std::string name = "leave";
		const std::string desc = "Leaves the current room.";
	public:
		void execute(CmdVec&);
		std::string getDesc() { return desc; }
		std::string getName() { return name; }
	};
}
