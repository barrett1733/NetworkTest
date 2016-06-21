#include "Command.h"
#include <algorithm>

using namespace std;
using namespace Commands;

CmdVec Commands::parseCommand(std::string cmd)
{
	transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

	CmdVec cmdVec;
	cmdVec.reserve(10);

	cmdVec.push_back("");
	if (!cmd.empty())
	{
		for (int i = 0; i < cmd.length(); i++)
		{
			if (cmd[i] == '-')
				cmdVec.push_back("");
			else if (cmd[i] != ' ')
				cmdVec.back().push_back(cmd[i]);
		}
	}
	return cmdVec;
}