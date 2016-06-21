#pragma once
#include <string>
#include <iostream>
#include <thread>
#include <WinSock2.h>
#include <mutex>

struct Options
{
	bool quit = false;
	std::string username = "";
	std::string msg = "";
	SOCKET client;
	bool connected = false;
};

class OptionsHandler
{
	static Options* opts;
	std::mutex mtx;
public:
	OptionsHandler() {}
	OptionsHandler(const OptionsHandler& optsHandle) { opts = optsHandle.opts; }
	static void registerOptions(Options& _opts);
	bool canQuitProgram();
	void quitProgram();
	void setUsername(std::string usr);
	std::string getUsername();
	void setMsg(std::string msg);
	std::string getMsg();
	SOCKET getClientSocket();
	void setClientSocket(SOCKET);
	void print() { std::cout << opts << std::endl; }
};