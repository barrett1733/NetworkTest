#include "CommandThread.h"
#include "Command.h"

using namespace std;
using namespace Commands;

void CommandThread::run()
{
	msg = OptionsHandler::getMsg();
	if (!msg.empty())
	{
		if (msg.at(0) == '/') // command
		{
			cmd = msg.substr(1, msg.size() - 1);
			cmdMap.execute(parseCommand(cmd));
		}
		OptionsHandler::setMsg("");
	}
}