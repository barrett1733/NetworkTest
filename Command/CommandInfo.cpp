#include "CommandInfo.h"

using namespace std;
using namespace Commands;

void Commands::CommandInfo::execute(CmdVec &args)
{
	if (optsHandle.getClientSocket() != NULL)
	{
		sockaddr_in info = Net::getPeerInfo(optsHandle.getClientSocket());
		char ipaddr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(info.sin_addr.S_un.S_addr), ipaddr, INET_ADDRSTRLEN);
		cout << "Connected to " << ipaddr << ":" << info.sin_port << endl;
	}
	else
		cout << "Not connected.\n";
}
