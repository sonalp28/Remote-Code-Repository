#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// IComm.h			: interface for message-passing communication facility								//
// ver 1.0																								//
// Platform         : Dell Inspiron 13 - Windows 10, Visual Studio 2017                                 //-|_ 
// Language         : C++ using the facilities of the standard C++ Libraries                            //-|  <----------Requirement 1---------->
// Application      : Project 4 [Remote Code Repository] Object Oriented Design CSE-687 Spring'18		//
// Author           : Dr. Jim Fawcett, EECS, SU                                                         // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
* interface for message-passing communication facility
*
* Public Interface:
* =================
* static IComm* create(const std::string& machineAddress, size_t port) - function to create comm channel on given machine & port address
* virtual void start() = 0 -  virtual function to start comm channel
* virtual void stop() = 0 -  virtual function to stop comm channel
* virtual void postMessage(Message msg) = 0 - virtual function to post comm message 
* virtual Message getMessage() = 0 -  virtual function to get comm message 
* virtual std::string name() = 0 -  virtual function to return comm name 
* virtual ~IComm() - virtual destructor
* 
* Required Files:
* ===============
* Message.h, IComm.h
* 
* Build Command:
* ==============
* devenv repo.sln /rebuild debug
*
* Maintenance History:
* ====================
* ver 1.0 : 30 March 18
* - first release
*/

#include <string>
#include "../Message/Message.h"

namespace MsgPassingCommunication
{
	class IComm
	{
	public:
		static IComm* create(const std::string& machineAddress, size_t port);
		virtual void start() = 0;
		virtual void stop() = 0;
		virtual void postMessage(Message msg) = 0;
		virtual Message getMessage() = 0;
		virtual std::string name() = 0;
		virtual ~IComm() {}
	};
}