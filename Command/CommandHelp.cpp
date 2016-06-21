#include "CommandHelp.h"
#include "CommandMap.h"

using namespace std;
using namespace Commands;

void CommandHelp::execute(CmdVec& cmdVec)
{
	cout << "Help Menu\n\n";
	CommandMap::NameDescList list = CommandMap::getCommandNameDescList();
	for (int i = 0; i < list.size(); i++)
	{
		cout << "/" << list[i].first << " = " << list[i].second << endl;
	}
}
