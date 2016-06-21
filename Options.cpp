#include "Options.h"

Options* OptionsHandler::opts;

void OptionsHandler::registerOptions(Options& _opts)
{
	opts = &_opts;
}

bool OptionsHandler::canQuitProgram()
{
	return opts != NULL ? opts->quit : true;
}

void OptionsHandler::quitProgram()
{
	if (opts != NULL)
	{
		mtx.lock();
		opts->quit = true;
		mtx.unlock();
	}
}

void OptionsHandler::setUsername(std::string usr)
{
	if (opts != NULL)
	{
		mtx.lock();
		opts->username = usr;
		mtx.unlock();
	}
}

std::string OptionsHandler::getUsername()
{
	return opts != NULL ? opts->username : "ERROR - Username";
}

void OptionsHandler::setMsg(std::string msg)
{
	if (opts != NULL)
	{
		mtx.lock();
		opts->msg = msg;
		mtx.unlock();
	}
}

std::string OptionsHandler::getMsg()
{
	return opts != NULL ? opts->msg : "ERROR - Message";
}

SOCKET OptionsHandler::getClientSocket()
{
	return opts != NULL ? opts->client : NULL;
}

void OptionsHandler::setClientSocket(SOCKET sock)
{
	if (opts != NULL)
	{
		mtx.lock();
		opts->client = sock;
		mtx.unlock();
	}
}

