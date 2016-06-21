#include "InputThread.h"

using namespace std;

void InputThread::getInput(string& input)
{
	getline(cin, input);
}

void InputThread::run()
{
	getInput(input);
	optsHandle.setMsg(input);
}