#pragma once
#include <map>
#include <vector>
#include <memory>
#include "Command.h"

namespace Commands
{
	class CommandMap
	{
		typedef std::unique_ptr<Command> CmdUniqPtr;
		typedef std::vector<CmdUniqPtr> CmdList;
		typedef std::map<std::string, Command*> CmdMap;
		static CmdList cmdList;
		static CmdMap cmdMap;
		static std::vector<std::string> cmdNameList, cmdDescList;
	public:
		typedef std::vector<std::pair<std::string, std::string>> NameDescList;
		static void loadCmdMap();
		static void deleteCmdMap();
		static NameDescList getCommandNameDescList();
		void execute(CmdVec&);
	};
}