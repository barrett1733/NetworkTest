#pragma once
#include "Options.h"
#include <memory>

class Threaded
{
public:
	virtual void run() = 0;
};

typedef std::unique_ptr<Threaded> ThreadedPtr;

class ThreadWrapper
{
	OptionsHandler optsHandle;
public:
	void run(Threaded*);
};

