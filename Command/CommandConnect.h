#pragma once
#include "Command.h"
#include "../net.h"

namespace Commands
{
	class CommandConnect : public Command, public Net
	{
		const std::string name = "connect";
		const std::string desc = "Use /connect -<insert ip address> to connect to specified ip address.";
	public:
		void execute(CmdVec&);
		std::string getDesc() { return desc; }
		std::string getName() { return name; }
	};
}
