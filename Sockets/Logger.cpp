//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Logger.cpp		: log text messages to std::ostream										            //
// ver 1.0																								//
//------------------------------------------------------------------------------------------------------//
// Jim Fawcett (c) copyright 2015																		//
// All rights granted provided this copyright notice is retained										//
//------------------------------------------------------------------------------------------------------//
// Platform         : Dell Inspiron 13 - Windows 10, Visual Studio 2017                                 //-|_ 
// Language         : C++ using the facilities of the standard C++ Libraries                            //-|  <----------Requirement 1---------->
// Application      : Project 4 [Remote Code Repository] Object Oriented Design CSE-687 Spring'18       //
// Author			: Jim Fawcett, CST 4-187, Syracuse University										//
//					  (315) 443-3948, jfawcett@twcny.rr.com												//
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package supports logging for multiple concurrent clients to a
* single std::ostream.  It does this be enqueuing messages in a
* blocking queue and dequeuing with a single thread that writes to
* the std::ostream.
*
* Public interface:
* ------------------
* void Logger::write(const std::string& msg) - send text message to std::ostream
* void Logger::flush() - flush ostream buffer
* void Logger::title(const std::string& msg, char underline) - gives title
* void Logger::attach(std::ostream* pOut) - attach logger to existing std::ostream
* void Logger::start() - start logging
* void Logger::stop(const std::string& msg) - stop logging
* Logger::~Logger() - stop logging thread
*
* Build Process:
* --------------
* Required Files: Logger.h, Logger.cpp, Utilities.h, Utilities.cpp
*
* Build Command: devenv logger.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 22 Feb 2016
* - first release
*
*/
#include <functional>
#include <Windows.h>
#include "Logger.h"
#include "../Utilities/Utilities.h"
/*

*/
//----< send text message to std::ostream >--------------------------
void Logger::write(const std::string& msg)
{
	if (_ThreadRunning)
		_queue.enQ(msg);
}

//----< flush ostream buffer >---------------------------------------
void Logger::flush()
{
	if (_ThreadRunning)
	{
		while (_queue.size() > 0)  // wait for logger queue to empty
			::Sleep(50);
		_pOut->flush();
	}
}

//----< gives title >------------------------------------------------
void Logger::title(const std::string& msg, char underline)
{
	std::string temp = "\n  " + msg + "\n " + std::string(msg.size() + 2, underline);
	write(temp);
}

//----< attach logger to existing std::ostream >---------------------
void Logger::attach(std::ostream* pOut)
{
	_pOut = pOut;
}

//----< start logging >----------------------------------------------
void Logger::start()
{
	if (_ThreadRunning)
		return;
	_ThreadRunning = true;
	std::function<void()> tp = [=]() {
		while (true)
		{
			std::string msg = _queue.deQ();
			if (msg == "quit")
			{
				_ThreadRunning = false;
				break;
			}
			*_pOut << msg;
		}
	};
	std::thread thr(tp);
	thr.detach();
}

//----< stop logging >-----------------------------------------------
void Logger::stop(const std::string& msg)
{
	if (_ThreadRunning)
	{
		if (msg != "")
			write(msg);
		write("quit");  // request thread to stop
		while (_ThreadRunning)
			/* wait for thread to stop*/
			;
	}
}

//----< stop logging thread >----------------------------------------
Logger::~Logger()
{
	stop();
}

/*<------------------------------------------- test stub ------------------------------------------>*/
#ifdef TEST_LOGGER

Cosmetic cosmetic;

using Util = Utilities::StringHelper;

int main()
{
	//Util::Title("Testing Logger Class");
	Logger log;
	log.attach(&std::cout);
	log.write("\n  won't get logged - not started yet");
	log.start();
	log.title("Testing Logger Class", '=');
	log.write("\n  one");
	log.write("\n  two");
	log.write("\n  fini");
	log.stop();
	log.write("\n  won't get logged - stopped");
	log.start();
	log.write("\n  starting again");
	log.write("\n  and stopping again");
	log.stop("\n  terminating now");

	StaticLogger<1>::attach(&std::cout);
	StaticLogger<1>::start();
	StaticLogger<1>::write("\n");
	StaticLogger<1>::title("Testing StaticLogger class");
	StaticLogger<1>::write("\n  static logger at work");
	Logger& logger = StaticLogger<1>::instance();
	logger.write("\n  static logger still at work");
	logger.stop("\n  stopping static logger");
}

#endif
