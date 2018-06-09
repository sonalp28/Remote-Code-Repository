#ifndef LOGGER_H
#define LOGGER_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Logger.h			: log text messages to std::ostream									                //
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

#include <iostream>
#include <string>
#include <thread>
#include "Cpp11-BlockingQueue.h"

class Logger
{
public:
	Logger() {}
	void attach(std::ostream* pOut);
	void start();
	void stop(const std::string& msg = "");
	void write(const std::string& msg);
	void flush();
	void title(const std::string& msg, char underline = '-');
	~Logger();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
private:
	std::thread* _pThr;
	std::ostream* _pOut;
	BlockingQueue<std::string> _queue;
	bool _ThreadRunning = false;
};

template<int i>
class StaticLogger
{
public:
	static void attach(std::ostream* pOut) { _logger.attach(pOut); }
	static void start() { _logger.start(); }
	static void stop(const std::string& msg = "") { _logger.stop(msg); }
	static void write(const std::string& msg) { _logger.write(msg); }
	static void flush() { _logger.flush(); }
	static void title(const std::string& msg, char underline = '-') { _logger.title(msg, underline); }
	static Logger& instance() { return _logger; }
	StaticLogger(const StaticLogger&) = delete;
	StaticLogger& operator=(const StaticLogger&) = delete;
private:
	static Logger _logger;
};

template<int i>
Logger StaticLogger<i>::_logger;

struct Cosmetic
{
	~Cosmetic() { std::cout << "\n\n"; }
};

#endif
