#include "CommandLeave.h"

using namespace std;
using namespace Commands;

void CommandLeave::execute(CmdVec& cmdVec)
{
	cout << "executing leave.....\n";
	closesocket(OptionsHandler::getClientSocket());
}

