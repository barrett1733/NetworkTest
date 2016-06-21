#include "CommandMap.h"
#include "CommandConnect.h"
#include "CommandHelp.h"
#include "CommandInfo.h"
#include "CommandLeave.h"
#include "CommandQuit.h"

using namespace std;
using namespace Commands;

CommandMap::CmdList CommandMap::cmdList;
CommandMap::CmdMap CommandMap::cmdMap;
std::vector<std::string> CommandMap::cmdNameList, CommandMap::cmdDescList;

void CommandMap::loadCmdMap()
{
	if (cmdList.empty())
	{
		cmdList.push_back(CmdUniqPtr(new CommandInfo()));
		cmdList.push_back(CmdUniqPtr(new CommandConnect()));
		cmdList.push_back(CmdUniqPtr(new CommandHelp()));
		cmdList.push_back(CmdUniqPtr(new CommandLeave()));
		cmdList.push_back(CmdUniqPtr(new CommandQuit()));
	}

	if (cmdMap.empty())
	{
		for (int i = 0; i < cmdList.size(); i++)
		{
			cmdMap[cmdList[i]->getName()] = cmdList[i].get();
		}
	}

	if (cmdNameList.empty())
	{
		for (int i = 0; i < cmdList.size(); i++)
		{
			cmdNameList.push_back(cmdList[i]->getName());
		}
	}

	if (cmdDescList.empty())
	{
		for (int i = 0; i < cmdList.size(); i++)
		{
			cmdDescList.push_back(cmdList[i]->getDesc());
		}
	}
}

void CommandMap::execute(CmdVec& cmdVec)
{
	if (!cmdVec[0].empty())
	{
		if (cmdMap.find(cmdVec[0]) != cmdMap.end())
		{
			cmdMap[cmdVec[0]]->execute(cmdVec);
		}
		else
		{
			cout << "Invaild command\n";
		}
	}
}

void CommandMap::deleteCmdMap()
{
	if (!cmdMap.empty())
	{
		for (CmdMap::iterator iter = cmdMap.begin(); iter != cmdMap.end(); ++iter)
		{
			iter->second = NULL;
		}
		cmdMap.clear();
	}
}

CommandMap::NameDescList Commands::CommandMap::getCommandNameDescList()
{
	NameDescList list;
	for (int i = 0; i < cmdNameList.size(); i++)
	{
		list.push_back(pair<string, string>(cmdNameList[i], cmdDescList[i]));
	}
	return list;
}
