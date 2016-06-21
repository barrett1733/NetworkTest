#pragma once
#include <iostream>
#include <string>
#include "Options.h"
#include "ThreadWrapper.h"

class InputThread : public Threaded//, OptionsHandler
{
	OptionsHandler optsHandle;
	std::string input;
	void getInput(std::string&);
public:
	void run();
};

