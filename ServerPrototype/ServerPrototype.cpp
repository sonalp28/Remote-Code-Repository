//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ServerPrototype.cpp	: Console App that processes incoming messages										//
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

#include "ServerPrototype.h"
#include "../FileSystem/FileSystem.h"
#include <chrono>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace MsgPassComm = MsgPassingCommunication;

using namespace Repository;
using namespace FileSystem;
using Msg = MsgPassingCommunication::Message;

/*

*/
/*<----------------------------- function to get file names present in server repository ------------------------------------>*/
Files Server::getFiles(const Repository::SearchPath& path)
{
	return Directory::getFiles(path);
}

/*<--------------------------- function to get directory names present in server repository --------------------------------->*/
Dirs Server::getDirs(const Repository::SearchPath& path)
{
	return Directory::getDirectories(path);
}

/*<------------------------------------ function to show the message content ------------------------------------------------>*/
template<typename T>
void show(const T& t, const std::string& msg)
{
	std::cout << "\n  " << msg.c_str();
	for (auto item : t)
	{
		std::cout << "\n    " << item.c_str();
	}
}

/*<------------------------------ function that demonstrate meeting of requirement 1 ---------------------------------------->*/
void Server::DemoReq1() {
	std::cout << "\n\nRequirement 1[a] - Shall use Visual Studio 2017 and the standard C++ libraries, as provided in the ECS computer labs";
	std::cout << "\n====================================================================================================================\n";
	std::cout << "\n " << typeid(std::function<bool()>).name() << ", declared in this function, " << "is only valid for C++11 and later versions.\n";
}

/*<------------------------------ function that demonstrate meeting of requirement 2 ---------------------------------------->*/
void Server::DemoReq2() {
	std::cout << "\n\nRequirement 2 - Shall provide a Repository Server that provides";
	std::cout << "\n======================================================================================\n";
	std::cout << "\n 1. It is used for providing functionality to check-in, check-out, and browse";
	std::cout << "\n 2. It is used to do browsing on repository server specified by NoSql database queries";
}

/*<------------------------------ function that demonstrate meeting of requirement 2 ---------------------------------------->*/
void Server::DemoReq4() {
	std::cout << "\n\nRequirement 4, 5, 6 - Shall provide an asynchronous message-passing communication channel";
	std::cout << "\n======================================================================================\n";
	std::cout << "\n 1. It is used for all communication between Clients and the Remote Repository Server";
	std::cout << "\n 2. It uses HTTP style messages using asynchronous one-way messaging";
	std::cout << "\n 3. It uses sending and receiving blocks of bytes6 for file transfer";
}

/*<------------ function that calles the check-in realted packages and do the check in functionality of a file--------------->*/
bool Server::checkin(std::string name, std::string description, std::string author, std::string category, std::string status, std::string path, std::string children) {
	bool checkin_result = false;
	std::size_t found = name.find_first_of(".");
	std::string dir = name.substr(0, found);
	std::string source_path = clientPath + name;						//e.g - ../ClientRepository/Check-in/display.h
	std::string dest_path = storageRoot + dir + "/" + name;			    //e.g - ../ServerRepository/display/display.h
	int version_count = 1;
	int count = atoi(repo.getlastcount(name).c_str());
	if (count > 0) {
		version_count = count;
		if (repo.getLastStatus(name) == "close")
			version_count++;
		dest_path = dest_path + "." + std::to_string(count);
		checkin_result = repo.checkin(source_path, dest_path, version_count, description, author, category, status, children);
	}	
	else
		checkin_result = repo.do_checkin(source_path, dest_path, version_count, description, author, category, status, children);
	checkedinFileName = name + "." + std::to_string(version_count);
	repo.display_db();
	return checkin_result;
}

/*<-------------------------- function to checkout a file from repository --------------------------------------------------->*/
bool Server::checkout(std::string fileName) {
	bool checkout_result = true;
	std::vector<std::string> data;
	std::stringstream ss(fileName);
	std::string token;
	while (getline(ss, token, ','))
		data.push_back(token);
	for (size_t i = 0; i < data.size(); i++) {
		std::size_t found = data.at(i).find_first_of(".");
		std::string dir = data.at(i).substr(0, found);
		std::string source_path = storageRoot + dir + "/" + data.at(i);			    //e.g - ../ServerRepository/display/display.h
		std::string dest_path = clientCheckoutPath + data.at(i);						//e.g - ../ClientRepository/Check-in/display.h
		checkout_result &= repo.checkout(source_path, dest_path);
	}	
	return checkout_result;
}

/*<--------------------------------function to get catgories names from repository------------------------------------------->*/
std::string Server::getCatgoryNames() {
	return repo.getCatgories();
}

/*<--------------------------------function to get catgory file names from repository---------------------------------------->*/
std::string Server::getCatgoryFileNames(std::string catgName) {
	return repo.getCatgoryFiles(catgName);
}

/*<---------------------- function to give the data stored in NoSqlDb in the form of string --------------------------------->*/
std::string Server::getDbData() {
	return repo.getDbData();
}

/*<-------------------------- function to get query result as per the data given -------------------------------------------->*/
std::string Server::getQueryResult(std::string fname, std::string catg, std::string depend, std::string version) {
	return repo.getQueryResult(fname,catg,depend,version);
}


/*<------------------------ standard function which accepts msg & replies back reply msg ------------------------------------>*/
std::function<Msg(Msg)> echo = [](Msg msg) {
	Msg reply = msg;
	reply.to(msg.from());
	reply.from(msg.to());
	return reply;
};

/*<------------------------ standard function which accepts msg & replies back reply msg ------------------------------------>*/
std::function<Msg(Msg)> getFiles = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command("getFiles");
	std::string path = msg.value("path");
	if (path != "")
	{
		std::string searchPath = storageRoot;
		if (path != ".")
			searchPath = searchPath + "\\" + path;
		Files files = Server::getFiles(searchPath);
		size_t count = 0;
		for (auto item : files)
		{
			std::string countStr = Utilities::Converter<size_t>::toString(++count);
			reply.attribute("file" + countStr, item);
		}
	}
	else
	{
		std::cout << "\n  getFiles message did not define a path attribute";
	}
	return reply;
};

/*<------------------------ standard function which accepts msg & replies back reply msg ------------------------------------>*/
std::function<Msg(Msg)> getDirs = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command("getDirs");
	std::string mesg = msg.value("message");
	if (mesg != "")
	{
		Files dirs = Server::getDirs(storageRoot);
		std::string dirs_str;
		for (auto item : dirs)
		{
			dirs_str += item + ",";
		}
		reply.attribute("dir", dirs_str);
	}
	else
	{
		std::cout << "\n  getDirs message did not define a path attribute";
	}
	return reply;
};

/*<------------------------ standard function which accepts msg & replies back reply msg ------------------------------------>*/
std::function<Msg(Msg)> getConnectMsg = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command("getConnectMsg");
	std::string msg_ = msg.value("message");
	if (msg_ != "")
	{
		//MsgPassingCommunication::EndPoint serverEndPoint("localhost", stoi(msg_.substr(msg_.length()-4,msg_.length())));
		reply.attribute("message", "Connection Established successfully!");
	}
	else
	{
		std::cout << "\n  getConnectMsg message did not define a FileName attribute";
	}
	return reply;
};

/*<------------------------ standard function which accepts msg & replies back reply msg ------------------------------------>*/
std::function<Msg(Msg)> getCatBrowseMsg = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command("getCatBrowseMsg");
	std::cout << "\n------------------------Performing Query on NoSqlDb to category names-----------------------------------------\n";
	reply.attribute("message", Server::getCatgoryNames());
	std::cout << "\n--------------------------------------------------------------------------------------------------------------\n";
	return reply;
};

/*<------------------------ standard function which accepts msg & replies back reply msg ------------------------------------>*/
std::function<Msg(Msg)> getCatFileMsg = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command("getCatFileMsg");
	std::cout << "\n-----------------Performing Query on NoSqlDb to get no parent files for particular category-------------------\n";
	reply.attribute("message", Server::getCatgoryFileNames(msg.value("catgName")));
	std::cout << "\n--------------------------------------------------------------------------------------------------------------\n";
	return reply;
};

/*<------------------------ standard function which accepts msg & replies back reply msg ------------------------------------>*/
std::function<Msg(Msg)> getQueryMsg = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command("getQueryMsg");
	std::cout << "\n-------------------------------------Performing Query OR on NoSqlDb-------------------------------------------\n";
	reply.attribute("message", Server::getQueryResult(msg.value("fileName"), msg.value("category"), msg.value("dependency"), msg.value("version")));
	std::cout << "\n--------------------------------------------------------------------------------------------------------------\n";
	return reply;
};

/*<------------------------ standard function which accepts msg & replies back reply msg ------------------------------------>*/
std::function<Msg(Msg)> getCheckinMsg = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command("getCheckinMsg");
	if (msg.value("sendingFile") != "") { 
		std::cout << "\n------------------------------------------Performing Check-In----------------------------------------------\n";
		std::cout << "  Receiving file : " << msg.value("sendingFile") << "\n";
		bool result = Server::checkin(msg.value("sendingFile"), msg.value("descr"), msg.value("author"), msg.value("category"), msg.value("status"), msg.value("path"), msg.value("children"));
		if (result) { 
			reply.attribute("message", checkedinFileName + ": Check-in is successful!"); 
		}
		else { 
			reply.attribute("message", checkedinFileName + ": Check-in is failed!"); 
		}
	}
	else
	{
		std::cout << "\n  getFiles message did not define a path attribute";
	}
	
	return reply;
};

/*<------------------------ standard function which accepts msg & replies back reply msg ------------------------------------>*/
std::function<Msg(Msg)> getDependent = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command("getDependent");
	std::string file_name = msg.value("fileName");
	std::cout << "\n---------------------------Performing Query on NoSqlDb to get dependent files---------------------------------\n";
	if (file_name != "") {
		reply.attribute("dependentFiles", repo.getDependentFiles(msg.value("fileName")));
	}
	else
	{
		std::cout << "\n  getCheckOutMsg message did not define a FileName attribute";
	}
	std::cout << "\n--------------------------------------------------------------------------------------------------------------\n";
	return reply;
};

/*<------------------------ standard function which accepts msg & replies back reply msg ------------------------------------>*/
std::function<Msg(Msg)> getCheckOutMsg = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command("getCheckOutMsg");
	std::string file_name = msg.value("FileName");
	std::cout << "\n------------------------------------------Performing Check-Out----------------------------------------------\n";
	if (file_name != "")
	{
		bool result = Server::checkout(msg.value("FileName") + "," + msg.value("dependFileName"));
		if (result) { 
			reply.attribute("message", "Check-out for file : " + msg.value("FileName") + "," + msg.value("dependFileName") + " is successful!"); 
		}
		else { 
			reply.attribute("message", "Check-out for file : " + msg.value("FileName") + "," + msg.value("dependFileName") + " is failed!");
		}
	}
	else
	{
		std::cout << "\n  getCheckOutMsg message did not define a FileName attribute";
	}
	return reply;
};

/*<------------------------ standard function which accepts msg & replies back reply msg ------------------------------------>*/
std::function<Msg(Msg)> getViewFileMsg = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command("getViewFileMsg");
	bool copy_status = false;
	std::string file_name = msg.value("sendFile");
	std::size_t found = file_name.find_first_of(".");
	std::string dir = file_name.substr(0,found);
	std::string source_path = storageRoot + dir + "/" + file_name;
	std::string dest_path = copyFilePath + file_name;
	std::string content = std::to_string(file_name.length());
	content += file_name;
	if (file_name != "")
	{
		if (FileSystem::File::exists(source_path))
			copy_status = FileSystem::File::copy(source_path, dest_path, false);
		if (copy_status)
		{
			std::cout << "\n\nRequirement 2[a] - Transferring files between Clients and Server using message passing comm";
			std::cout << "\n===========================================================================================\n\n";
			reply.attribute("message", "../../" + dest_path);		//going two back directories bez GUI exe file will be inside 2 directories 
		}
		else
			reply.attribute("message", "sorry file doesn't exist!");				
	}
	else
	{
		std::cout << "\n  getViewFileMsg message did not define a FileName attribute";
	}
	return reply;
};

/*<------------------------ standard function which accepts msg & replies back reply msg ------------------------------------>*/
std::function<Msg(Msg)> getMetadataMsg = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command("getMetadataMsg");
	std::string file_name = msg.value("Metadata");
	reply.attribute("dbdata", Server::getDbData());
	return reply;
};

/*<---------------------------------------------- test stub ---------------------------------------------------------------->*/
#ifdef TEST_SERVER
int main()
{
	SetConsoleTitleA("Server Repository");
	std::cout << "\n                                           Remote Repository Server";
	std::cout << "\n====================================================================================================================\n";

	repo.getBackDb();
	repo.display_db();

	Server server(serverEndPoint, "ServerPrototype");
	server.DemoReq1();
	server.DemoReq2();
	server.DemoReq4();
	server.start();
	
	server.addMsgProc("getConnectMsg", getConnectMsg);
	server.addMsgProc("getCatBrowseMsg", getCatBrowseMsg);
	server.addMsgProc("getCatFileMsg", getCatFileMsg);
	server.addMsgProc("getQueryMsg", getQueryMsg);
	server.addMsgProc("getCheckinMsg", getCheckinMsg);
	server.addMsgProc("getDependent", getDependent);
	server.addMsgProc("getCheckOutMsg", getCheckOutMsg);
	server.addMsgProc("getViewFileMsg", getViewFileMsg);
	server.addMsgProc("getMetadataMsg", getMetadataMsg);
	server.processMessages();

	Msg msg(serverEndPoint, serverEndPoint);  // send to self
	std::cout << "\n\n  press enter to exit\n\n";
	std::cin.get();
	std::cout << "\n";

	msg.command("serverQuit");
	server.postMessage(msg);
	server.stop();
	return 0;
}
#endif // TEST_SERVER



