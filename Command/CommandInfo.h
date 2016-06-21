#pragma once
#include "Command.h"
#include "../net.h"
#include "../Options.h"

namespace Commands
{
	class CommandInfo : public Command, Net
	{
		OptionsHandler optsHandle;
		const std::string name = "info";
		const std::string desc = "Gets the info of the current connection.";
	public:
		void execute(CmdVec&);
		std::string getDesc() { return desc; }
		std::string getName() { return name; }
	};
}
