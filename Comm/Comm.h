#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Comm.h			: message-passing communication facility								            //
// ver 2.2																								//
// Platform         : Dell Inspiron 13 - Windows 10, Visual Studio 2017                                 //-|_ 
// Language         : C++ using the facilities of the standard C++ Libraries                            //-|  <----------Requirement 1---------->
// Application      : Project 4 [Remote Code Repository] Object Oriented Design CSE-687 Spring'18		//
// Author           : Dr. Jim Fawcett, EECS, SU                                                         // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package defines Sender and Receiver classes.
*  - Sender uses a SocketConnecter and supports connecting to multiple
*    sequential endpoints and posting messages.
*  - Receiver uses a SocketListener which returns a Socket on connection.
*  It also defines a Comm class
*  - Comm simply composes a Sender and a Receiver, exposing methods:
*    postMessage(Message) and getMessage()
*
* Public Interface:
* -------------------
* inline IComm* IComm::create(const std::string& machineAddress, size_t port) - function to create an instance of Comm on the native heap
* Receiver::Receiver(EndPoint ep, const std::string& name) - constructor sets port
* BlockingQueue<Message>* Receiver::queue() - returns reference to receive queue
* template<typename CallableObject> void Receiver::start(CallableObject& co) - starts listener thread running callable object
* void Receiver::stop() - stops listener thread
* Message Receiver::getMessage() - retrieves received message
* Sender::Sender(const std::string& name) - constructor initializes endpoint object
* Sender::~Sender() - destructor waits for send thread to terminate
* void Sender::start() - starts send thread deQ, inspect, and send loop
* void Sender::stop() - stops send thread by posting quit message
* bool Sender::connect(EndPoint ep) - attempts to connect to endpoint ep
* void Sender::postMessage(Message msg) - posts message to send queue
* bool Sender::sendFile(Message msg) - sends binary file
* ClientHandler(BlockingQueue<Message>* pQ, const std::string& name = "clientHandler") - acquire reference to shared rcvQ
* ~ClientHandler() - shutdown message
* void setQueue(BlockingQueue<Message>* pQ) - set Blocking Queue
* std::string readMsg(Socket& socket) - frame message string by reading bytes from socket
* bool receiveFile(Message msg) - receive file blocks
* void operator()(Socket socket) - reads messages from socket and enQs in rcvQ
* Comm::Comm(EndPoint ep, const std::string& name) : rcvr(ep, name), sndr(name), commName(name) - constructor initializes endpoint object & name
* void Comm::start() - starts send thread deQ, inspect, and send loop
* void Comm::stop() - stops send thread by posting quit message
* void Comm::postMessage(Message msg) - posts message to send queue
* Message Comm::getMessage() - gets message from receive queue
* std::string Comm::name() - return name of the comm
*
*  Required Files:
*  ---------------
*  Comm.h, Comm.cpp,
*  Sockets.h, Sockets.cpp,
*  Message.h, Message.cpp,
*  Utilities.h, Utilities.cpp
*
* Build Command:
* ----------------
* devenv repo.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
*  ver 2.2 : 27 Mar 2018
*  - added interface IComm and object factory (static method in IComm)
*  - Comm now implements the IComm interface
*  - No change to code other that derive from interface and implement its create method
*  ver 2.1 : 25 Mar 2018
*  - added declaration of SocketSystem in Comm class
*  ver 2.0 : 07 Oct 2017
*  - added sendFile(...) as private member of Sender
*  - added receiveFile() as member of ClientHandler
*  ver 1.0 : 03 Oct 2017
*  - first release
*/

#include "../Message/Message.h"
#include "Cpp11-BlockingQueue.h"
#include "../Sockets/Sockets.h"
#include "IComm.h"
#include <string>
#include <thread>

using namespace Sockets;

namespace MsgPassingCommunication
{
	///////////////////////////////////////////////////////////////////
	// Receiver class
	class Receiver
	{
	public:
		Receiver(EndPoint ep, const std::string& name = "Receiver");
		template<typename CallableObject>
		void start(CallableObject& co);
		void stop();
		Message getMessage();
		BlockingQueue<Message>* queue();
	private:
		BlockingQueue<Message> rcvQ;
		SocketListener listener;
		std::string rcvrName;
	};

	///////////////////////////////////////////////////////////////////
	// Sender class
	class Sender
	{
	public:
		Sender(const std::string& name = "Sender");
		~Sender();
		void start();
		void stop();
		bool connect(EndPoint ep);
		void postMessage(Message msg);
	private:
		bool sendFile(Message msg);
		BlockingQueue<Message> sndQ;
		SocketConnecter connecter;
		std::thread sendThread;
		EndPoint lastEP;
		std::string sndrName;
	};

	///////////////////////////////////////////////////////////////////
	// Comm class
	class Comm : public IComm
	{
	public:
		Comm(EndPoint ep, const std::string& name = "Comm");
		void start();
		void stop();
		void postMessage(Message msg);
		Message getMessage();
		std::string name();
	private:
		Sender sndr;
		Receiver rcvr;
		std::string commName;
		Sockets::SocketSystem socksys_;
	};

	/*<----------------------------- function to create an instance of Comm on the native heap ----------------------------->*/
	inline IComm* IComm::create(const std::string& machineAddress, size_t port)
	{
		//std::cout << "\n  creating an instance of Comm on the native heap";
		EndPoint ep(machineAddress, port);
		IComm* pComm = new Comm(ep, "created Comm");
		return pComm;
	}
}