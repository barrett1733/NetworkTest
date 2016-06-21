#pragma once
#include <string>
#include "../Options.h"
#include "../ThreadWrapper.h"
#include "CommandMap.h"

namespace Commands
{
	class CommandThread : public Threaded, OptionsHandler
	{
		CommandMap cmdMap;
		std::string msg, cmd;
	public:
		void run();
	};
}