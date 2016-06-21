#include "client.h"
#include "server.h"
#include <thread>
#include <bitset>
#include <functional>

#include "testing.h"

using namespace std;
#define debug true

int main()
{
	if (debug)
	{
		test();
	}
	if (!debug)
	{/*
		string serverMode;
		InputHandler hInput;

		cout << "Server mode? (y or n)\n";
		getline(cin, serverMode);

		if (serverMode == "n")
		{
			cout << "Client mode.\n";
			string clientInput, username;
			bool connected = false;
			Client client;

			while (clientInput != "quit")
			{
				if (!connected)
				{
					cout << "Type ip address.\n";
					getline(cin, clientInput);

					if (client.connectTo(clientInput))
					{
						cout << "Enter username.\n";
						getline(cin, username);
						cout << endl;
						connected = true;
					}
				}
				else
				{
					cout << username << ":> ";
					getline(cin, clientInput);

					client.sendData(username, clientInput);
				}
			}
		}
		else
		{
			cout << "Server mode.\n";

			Server server;
			string input;
			server.start();
			server.runServer();
			while (input != "quit")
			{
				getline(cin, input);
			}
		}*/
	}
	cin.ignore();
	return 0;
}