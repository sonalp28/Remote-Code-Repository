#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// ServerPrototype.h: Console App that processes incoming messages										//
// ver 1.2																								//
// Platform         : Dell Inspiron 13 - Windows 10, Visual Studio 2017                                 //-|_ 
// Language         : C++ using the facilities of the standard C++ Libraries                            //-|  <----------Requirement 1---------->
// Application      : Project 4 [Remote Code Repository] Object Oriented Design CSE-687 Spring'18       //
// Author           : Sonal Patil, Syracuse University                                                  //
//                    spatil06@syr.edu (408)-416-6291                                                   //  
// Source           : Dr. Jim Fawcett, EECS, SU                                                         // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
* ---------------------
*  Package contains one class, Server, that contains a Message-Passing Communication
*  facility. It processes each message by invoking an installed callable object
*  defined by the message's command key.
*
*  Message handling runs on a child thread, so the Server main thread is free to do
*  any necessary background processing (none, so far).
*
*  Public interface:
* --------------------
* inline Server::Server(MsgPassingCommunication::EndPoint ep, const std::string& name) - initialize server endpoint and give server a name
* inline void Server::start() - start server's instance of Comm
* inline void Server::stop() - stop Comm instance
* inline void Server::postMessage(MsgPassingCommunication::Message msg) - pass message to Comm for sending
* inline MsgPassingCommunication::Message Server::getMessage() - get message from Comm
* inline void Server::addMsgProc(Key key, ServerProc proc) - add ServerProc callable object to server's dispatcher
* inline void Server::processMessages() - start processing messages on child thread
* Files Server::getFiles(const Repository::SearchPath& path) - function to get file names present in server repository
* Dirs Server::getDirs(const Repository::SearchPath& path) - function to get directory names present in server repository
* template<typename T>void show(const T& t, const std::string& msg) - function to show the message content
* void Server::DemoReq1() - function that demonstrate meeting of requirement 1
* void Server::DemoReq2() - function that demonstrate meeting of requirement 2
* void Server::DemoReq4() - function that demonstrate meeting of requirement 4
* bool checkin(std::string name, std::string description, std::string author, std::string category, std::string status, std::string path, std::string children) - function that calls proper RepoCore function & gives back result
* bool checkout(std::string fileName) - function that calls proper RepoCore function & gives back result
* std::string getCatgoryNames() - function that calls proper RepoCore function & gives back result
* std::string getCatgoryFileNames(std::string catgName) - function that calls proper RepoCore function & gives back result
* std::string Server::getDbData() - function that calls proper RepoCore function & gives back result
* std::function<Msg(Msg)> echo = [](Msg msg) - standard function which accepts msg & replies back reply msg
* std::function<Msg(Msg)> getFiles = [](Msg msg) - standard function which accepts msg & replies back reply msg
* std::function<Msg(Msg)> getDirs = [](Msg msg) - standard function which accepts msg & replies back reply msg
* std::function<Msg(Msg)> getConnectMsg = [](Msg msg) - standard function which accepts msg & replies back reply msg
* std::function<Msg(Msg)> getCatBrowseMsg = [](Msg msg) - standard function which accepts msg & replies back reply msg
* std::function<Msg(Msg)> getCatFileMsg = [](Msg msg) - standard function which accepts msg & replies back reply msg
* std::function<Msg(Msg)> getCheckinMsg = [](Msg msg) - standard function which accepts msg & replies back reply msg
* std::function<Msg(Msg)> getDependent = [](Msg msg) - standard function which accepts msg & replies back reply msg
* std::function<Msg(Msg)> getCheckOutMsg = [](Msg msg) - standard function which accepts msg & replies back reply msg
* std::function<Msg(Msg)> getViewFileMsg = [](Msg msg) - standard function which accepts msg & replies back reply msg
* std::function<Msg(Msg)> getMetadataMsg = [](Msg msg) - standard function which accepts msg & replies back reply msg
*
*  Required Files:
* -----------------
*  ServerPrototype.h, ServerPrototype.cpp
*  Comm.h, Comm.cpp, IComm.h
*  Message.h, Message.cpp
*  FileSystem.h, FileSystem.cpp
*  Utilities.h
*
*  Build Command:
* ----------------
*  devenv repo.sln /rebuild debug
*
*  Maintenance History:
* ----------------------
* ver 1.2 : 5/01/2018
*  - third release - modified according to project 4 requirements + functionality related to Repository
* ver 1.1 : 4/10/2018
*  - second release - modified acording to project 3 requirements + some functionality related to Repository
*  ver 1.0 : 3/27/2018
*  - first release
*/
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <thread>
#include "../Message/Message.h"
#include "../Comm/Comm.h"
#include "../DbCore/DbCore.h"
#include "../DbCore/Payload.h"
#include "../RepoCore/RepoCore.h"
#include <windows.h>
#include <tchar.h>

using namespace NoSqlDb;
using namespace RepositoryCore;

namespace Repository
{
	using File = std::string;
	using Files = std::vector<File>;
	using Dir = std::string;
	using Dirs = std::vector<Dir>;
	using SearchPath = std::string;
	using Key = std::string;
	using Msg = MsgPassingCommunication::Message;
	using ServerProc = std::function<Msg(Msg)>;
	using MsgDispatcher = std::unordered_map<Key, ServerProc>;

	const SearchPath storageRoot = "../ServerRepository/";  // root for all server file storage
	const SearchPath copyFilePath = "../CopiedFIles/";  // root for all files that gets copied for client side
	const SearchPath clientPath = "../ClientRepository/Check-in/";
	const SearchPath clientCheckoutPath = "../ClientRepository/Check-out/";
	const MsgPassingCommunication::EndPoint serverEndPoint("localhost", 8082);  // listening endpoint

	RepositoryCore::RepoCore repo;
	std::string checkedinFileName = "";

	class Server
	{
	public:
		inline void Server::identify(std::ostream& out = std::cout) { out << "\n     \"" << __FILE__ << "\""; }
		Server(MsgPassingCommunication::EndPoint ep, const std::string& name);
		void start();
		void stop();
		void addMsgProc(Key key, ServerProc proc);
		void processMessages();
		void postMessage(MsgPassingCommunication::Message msg);
		MsgPassingCommunication::Message getMessage();
		static Dirs getDirs(const SearchPath& path = storageRoot);
		static Files getFiles(const SearchPath& path = storageRoot);
		static bool checkin(std::string name, std::string description, std::string author, std::string category, std::string status, std::string path, std::string children);
		static bool checkout(std::string fileName);
		static std::string getCatgoryNames();
		static std::string getCatgoryFileNames(std::string catgName);
		static std::string getDbData();
		static std::string getQueryResult(std::string fname, std::string catg, std::string depend, std::string version);
		void DemoReq1();
		void DemoReq2();
		void DemoReq4();
	private:
		MsgPassingCommunication::Comm comm_;
		MsgDispatcher dispatcher_;
		std::thread msgProcThrd_;
		std::vector<std::string> data;
	};
	
	//----< initialize server endpoint and give server a name >----------
	inline Server::Server(MsgPassingCommunication::EndPoint ep, const std::string& name)
		: comm_(ep, name) {}

	//----< start server's instance of Comm >----------------------------
	inline void Server::start()
	{
		comm_.start();
	}
	
	//----< stop Comm instance >-----------------------------------------
	inline void Server::stop()
	{
		if (msgProcThrd_.joinable())
			msgProcThrd_.join();
		comm_.stop();
	}

	//----< pass message to Comm for sending >---------------------------
	inline void Server::postMessage(MsgPassingCommunication::Message msg)
	{
		comm_.postMessage(msg);
	}

	//----< get message from Comm >--------------------------------------
	inline MsgPassingCommunication::Message Server::getMessage()
	{
		Msg msg = comm_.getMessage();
		return msg;
	}
	
	//----< add ServerProc callable object to server's dispatcher >------
	inline void Server::addMsgProc(Key key, ServerProc proc)
	{
		dispatcher_[key] = proc;
	}
	
	//----< start processing messages on child thread >------------------
	inline void Server::processMessages()
	{
		auto proc = [&]()
		{
			if (dispatcher_.size() == 0){ 
				std::cout << "\n  no server procs to call";	return;	
			}
			while (true)
			{
				try {
					Msg msg = getMessage();
					std::cout << "\nReceived message: from " << msg.from().toString();
					msg.show();
					if (msg.containsKey("verbose")) {
						std::cout << "\n"; msg.show();
					}
					if (msg.command() == "serverQuit") {
						break;
					}
					Msg reply = dispatcher_[msg.command()](msg);
					if (msg.to().port != msg.from().port) { // avoid infinite message loop
						postMessage(reply);
						std::cout << "\nPosted reply message: from " << reply.from().toString();
						reply.show();
					}
					else
						std::cout << "\n  server attempting to post to self";
				}
				catch (const std::exception& e) {
					std::cout << "Caused an error at Server side. Error details: " << e.what();
				}
			}
			std::cout << "\n  server message processing thread is shutting down";
		};
		std::thread t(proc);
		msgProcThrd_ = std::move(t);
	}
}
