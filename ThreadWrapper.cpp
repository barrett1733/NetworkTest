#include "ThreadWrapper.h"
#include <iostream>

void ThreadWrapper::run(Threaded* threadObj)
{
	while (!optsHandle.canQuitProgram())
	{
		threadObj->run();
	}
	std::cout << "Thread ended.\n";
}