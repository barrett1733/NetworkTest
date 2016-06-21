#include "testing.h"
#include <string>
#include <iostream>
#include <thread>
#include "PacketHandler.h"
#include "InputThread.h"
#include "Options.h"
#include "Command/CommandMap.h"
#include "Command/CommandThread.h"
#include "net.h"
#include "server.h"

using namespace std;

void testPacking(string sUsername, string sData)
{
	string rUsername, rTest;
	Buffer<SerializedPacket> recvBuf, sendBuf;
	PacketHandler pckhan;
	pckhan.pack(sendBuf, sUsername, sData);

	for (int i = 0; i < sendBuf.size(); i++)
	{
		recvBuf.push(sendBuf.get(i));
	}

	pckhan.unpack(recvBuf, rUsername, rTest);
	cout << rUsername << ":> " << rTest << endl;
}

void testDataPacking()
{
	string user = "steven";
	string test1 = "Hello World!";
	string test2 = "MacKellar's The American Printer was the dominant language style guide in the US at the time and ran to at least 17 editions between 1866 and 1893, and De Vinne's The Practice of Typography was the undisputed global authority on English-language typesetting style from 1901 until well past Dowding's first formal alternative spacing suggestion in the mid-1950s. Both the American and the UK style guides also specified that spaces should be inserted between punctuation and text. The MacKellar guide described these as hairspaces but itself used a much wider space than was then commonly regarded as a hairspace.[2] Spaces following words or punctuation were subject to line breaks, and spaces between words and closely associated punctuation were non-breaking. Additionally, spaces were (and still are today) varied proportionally in width when justifying lines, originally by hand, later by machine, now usually by software.";
	string test3 = "    11111222223333344444555556666677777888889999900000     22222333334444455555666667777788888999990000011111     33333444445555566666777778888899999000001111122222     44444555556666677777888889999900000111112222233333     55555666667777788888999990000011111222223333344444     66666777778888899999000001111122222333334444455555     77777888889999900000111112222233333444445555566666     88888999990000011111222223333344444555556666677777     99999000001111122222333334444455555666667777788888     ";
	testPacking(user, test1);
	testPacking(user, test2);
	testPacking(user, test3);
}

void test()
{
	Server server;
	Commands::CommandMap::loadCmdMap();
	Net net;
	Options opts;
	OptionsHandler optsHandle;
	optsHandle.registerOptions(opts);
	optsHandle.setClientSocket(net.openSocket());

	vector<thread> threads;

	threads.push_back(thread(&ThreadWrapper::run, ThreadWrapper(), &InputThread()));
	threads.push_back(thread(&ThreadWrapper::run, ThreadWrapper(), &Commands::CommandThread()));
	threads.push_back(thread(&ThreadWrapper::run, ThreadWrapper(), &server));

	for (int i = 0; i < threads.size(); i++)
		threads[i].join();

	Commands::CommandMap::deleteCmdMap();
}