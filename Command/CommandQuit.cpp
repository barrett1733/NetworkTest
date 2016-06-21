#include "CommandQuit.h"

using namespace std;
using namespace Commands;

void CommandQuit::execute(CmdVec& cmdVec)
{
	cout << "executing quit.....\n";
	quitProgram();
}
