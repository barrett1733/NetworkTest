#include "CommandConnect.h"

using namespace std;
using namespace Commands;

void CommandConnect::execute(CmdVec& cmdVec)
{
	cout << "executing connect.....\n";
	if (cmdVec.size() == 2)
	{
		if (Net::connectTo(OptionsHandler::getClientSocket(), Net::generateSocketAddr(cmdVec[1])))
		{
			string username;
			cout << "Enter username.\n";
			getline(cin, username);
			OptionsHandler::setUsername(username);
			cout << endl;

		}
		else
		{
			cout << "Connection failed.\n";
		}
	}
	else
	{
		cout << "Invalid arguments.\n";
	}
}
