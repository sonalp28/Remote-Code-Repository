//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Translater.cpp	: Translates messages to/from managed and native types								//
// ver 1.0																								//
// Platform         : Dell Inspiron 13 - Windows 10, Visual Studio 2017                                 //-|_ 
// Language         : C++ using the facilities of the standard C++ Libraries                            //-|  <----------Requirement 1---------->
// Application      : Project 4 [Remote Code Repository] Object Oriented Design CSE-687 Spring'18       //
// Author			: Jim Fawcett, CST 4-187, Syracuse University										//
//					  (315) 443-3948, jfawcett@twcny.rr.com												//
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
* ---------------------
*  This C++\Cli Package contains one class, Translater.  It's purpose is to convert
*  managed messages, CsMessage, to native messages, Message, and back.
*
* Public interface:
* ------------------
* Translater::Translater() - initialize endpoint
* inline void Translater::listen(CsEndPoint^ ep) - set client listen endpoint and start Comm
* inline CsMessage^ Translater::fromMessage(Message& msg) - convert native message to managed message
* inline Message Translater::fromCsMessage(CsMessage^ csMsg) - convert managed message to native message
* inline void Translater::postMessage(CsMessage^ csMsg) - uses comm to get message
* inline CsMessage^ Translater::getMessage() - get message from comm
*
*  Required Files:
* -----------------
*  Translater.h, Translater.cpp
*  CsMessage.h
*  Required References:
* ----------------------
*  CommLibWrapper.dll
*  Message.lib
*
*  Maintenance History:
* ----------------------
*  ver 1.0 : 3/27/2018
*  - first release
*/

#include "CsMessage.h"
#include "Translater.h"

using namespace MsgPassingCommunication;

/*<------------------------------------------- test stub ----------------------------------------------->*/
#ifdef TEST_Translator
int main()
{
	std::cout << "\n  Testing Translator Package";
	std::cout << "\n ============================\n";

	std::cout << "\n  testing CsEndPoint";
	std::cout << "\n --------------------";
	CsEndPoint^ ep = gcnew CsEndPoint;
	ep->machineAddress = "localhost";
	ep->port = 8081;
	String^ epStr = CsEndPoint::toString(ep);
	Console::Write("\n  {0}", epStr);
	CsEndPoint^ newEp = CsEndPoint::fromString(epStr);
	Console::Write("\n  machineAddress = {0}\n  port = {1}", newEp->machineAddress, newEp->port);
	std::cout << "\n";
	std::cout << "\n  testing CsMessage";
	std::cout << "\n -------------------";
	CsEndPoint^ ep2 = gcnew CsEndPoint;
	ep2->machineAddress = "localhost";
	ep2->port = 8080;
	CsMessage^ csMsg = gcnew CsMessage;
	csMsg->add("to", CsEndPoint::toString(ep2));
	csMsg->add("from", CsEndPoint::toString(ep));
	csMsg->add("command", "echo");
	csMsg->add("verbose", "beep");
	csMsg->show();
	std::cout << "\n";
	std::cout << "\n  testing Translater access to Comm";
	std::cout << "\n -----------------------------------";
	Translater^ tran = gcnew Translater;
	tran->listen(ep);
	for (size_t i = 0; i < 5; ++i)
	{
		tran->postMessage(csMsg);
		csMsg->remove("verbose");
	}
	for (size_t i = 0; i < 5; ++i)
	{
		CsMessage^ reply = tran->getMessage();
		reply->show();
	}
	std::cout << "\n\n";
	return 0;
}
#endif


