#ifndef SOCKETS_H
#define SOCKETS_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sockets.h		: C++ wrapper for Win32 socket api									                //
// ver 5.2														                                        //
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
*  Package Operations:
*  -------------------
*  Provides four classes that wrap the Winsock API:
*  Socket:
*  - provides all the functionality necessary to handle server clients
*  - created by SocketListener after accepting a request
*  - usually passed to a client handling thread
*  SocketConnecter:
*  - adds the ability to connect to a server
*  SocketListener:
*  - adds the ability to listen for connections on a dedicated thread
*  - instances of this class are the only ones influenced by ipVer().
*    clients will use whatever protocol the server provides.
*  SocketSystem:
*  - Loads and unloads winsock2 library.
*  - Declared once at beginning of execution
*
*  Public interface:
*  -----------------
* template<typename CallObj> bool SocketListener::start(CallObj& co) - SocketListener start function runs listener on its own thread
* SocketSystem::SocketSystem() - constructor starts up sockets by loading winsock lib
* SocketSystem::~SocketSystem() - destructor frees winsock lib
* Socket::Socket(IpVer ipver) - constructor sets TCP protocol and Stream mode
* Socket::Socket(::SOCKET sock) - promotes Win32 socket to Socket
* Socket::Socket(Socket&& s) - transfer socket ownership with move constructor
* Socket& Socket::operator=(Socket&& s) - transfer socket ownership with move assignment
* Socket::IpVer& Socket::ipVer() - get, set IP version
* void Socket::close() - close connection
* bool Socket::shutDownRecv() - tells receiver this socket won't call receive anymore
* bool Socket::shutDown() - tells receiver there will be no more sends or recvs
* Socket::~Socket() - destructor closes socket handle
* bool Socket::send(size_t bytes, byte* buffer) - send buffer
* bool Socket::recv(size_t bytes, byte* buffer) - recv buffer
* bool Socket::sendString(const std::string& str, byte terminator) - sends a terminator terminated string
* std::string Socket::recvString(byte terminator) - receives terminator terminated string
* std::string Socket::removeTerminator(const std::string& src) - strips terminator character that recvString includes
* size_t Socket::sendStream(size_t bytes, byte* pBuf) - attempt to send specified number of bytes, but may not send all
* size_t Socket::recvStream(size_t bytes, byte* pBuf) - attempt to recv specified number of bytes, but may not send all
* size_t Socket::bytesWaiting() - returns bytes available in recv buffer
* bool Socket::waitForData(size_t timeToWait, size_t timeToCheck) - waits for server data, checking every timeToCheck millisec
* SocketConnecter::SocketConnecter() - constructor inherits its base Socket's Win32 socket_ member
* SocketConnecter::SocketConnecter(SocketConnecter&& s) - move constructor transfers ownership of Win32 socket_ member
* SocketConnecter& SocketConnecter::operator=(SocketConnecter&& s) - move assignment transfers ownership of Win32 socket_ member
* SocketConnecter::~SocketConnecter() - destructor announces destruction if Verbose(true)
* bool SocketConnecter::connect(const std::string& ip, size_t port) - request to connect to ip and port
* SocketListener::SocketListener(size_t port, IpVer ipv) - constructs SocketListener, specifying type of protocol to use
* SocketListener::SocketListener(SocketListener&& s) - move constructor transfers ownership of Win32 socket_ member
* SocketListener& SocketListener::operator=(SocketListener&& s) - move assignment transfers ownership of Win32 socket_ member
* SocketListener::~SocketListener() - destructor announces destruction if Verbal(true)
* bool SocketListener::bind() - binds SocketListener to a network adddress on local machine
* bool SocketListener::listen() - put SocketListener in listen mode, doesn't block
* Socket SocketListener::accept() - accepts incoming requrests to connect - blocking call
* void SocketListener::stop() - request SocketListener to stop accepting connections
* 
*  Required Files:
*  ---------------
*  Sockets.h, Sockets.cpp,
*  Logger.h, Logger.cpp,
*  Utilities.h, Utililties.cpp,
*  WindowsHelpers.h, WindowsHelpers.cpp
*
*  Maintenance History:
*  --------------------
*  ver 5.2 : 05 Oct 2017
*  - changed Socket::recvString to append the terminating character,
*    newline by default
*  - added removeTerminator method to remove the newly added terminator
*    character
*  - modified error logging displays
*  ver 5.1 : 10 Apr 16
*  - Added sendStream and recvStream to support sending and receiving
*    file streams.  These simply wrap the native sockets send and recv.
*  ver 5.0 : 04 Mar 16
*  - Fixed bugs in Socket test stub, essentially stealing fixes from
*    ClientTest.cpp and ServerTest.cpp
*  - Didn't change any code in the Socket library itself
*  ver 4.9 : 04 Mar 16
*  - Added a single write statement in Socket::Listener::accept()
*  ver 4.8 : 22 Feb 16
*  - Replaced verbose I/O with Logger I/O
*  - Replaced ApplicationHelpers package with Utilities package
*  ver 4.7 : 04 Apr 15
*  - removed testBlockHandling declaration from Socket.cpp ClientHandler.
*    The implementation had already been removed, I just forgot the declaration.
*  - added test for INVALID_SOCKET in Socket::recvString.  The omission was
*    reported by Huanming Fang.  Thanks Huanming.
*  ver 4.6 : 30 Mar 15
*  - minor modification to comments, above, and in Socket class implem.
*  ver 4.5 : 30 Mar 15
*  - moved SocketListener::start(...) from cpp to h file since it is a
*    template method.
*  - renamed ClientProc to ClientHandler
*  - removed Block operations to avoid binding Socket package to
*    FileSystem package.  Will add buffer operations to the
*    FileSystem::File class to match the Socket buffer operations.
*  - gave ClientHandler a command interpreter to select a test process
*    - test string tranfers
*    - test buffer transfers
*    - client sends a string to select test mode
*    - test modes are (string, buffer, and stop)
*  - Created a Verbose class in AppHelpers package that locks stream io.
*    That helps to keep server and client io text from intermingling.
*    You can turn verbose mode off which silences output that isn't
*    marked "always".
*  - Fixed again the bug which prevented communicating with anything other
*    than the loopback by adding hints.ai_flags = AI_PASSIVE to
*    SocketListener member data.
*  - added more testing
*  ver 4.4 : 27 Mar 15
*  - minor changes to comments
*  - moved ClientHandler into test stub
*  ver 4.3 : 26 Mar 15
*  - fixed bug noticed by Tarun Rajput
*  - used '0' as terminator.  Should have been '\0'
*  ver 4.2 : 26 Mar 15
*  - several small changes to the Socket class interface
*  ver 4.1 : 25 Mar 15
*  - fixed connection bug that prevented connecting to anything
*    other than a loopback (localhost, 127.0.0.1, ::1) by
*    adding winsock code to SocketConnecter().
*  - removed low-level code from ClientProc
*    (server's client handler callable object)
*    replaced with code written to Socket interface
*  Ver 4.0 : 24 Mar 15
*  - first release of total redesign - had a known bug (see ver 4.1)
*/
/*
* ToDo:
* - make SocketSystem a reference counted instance of Socket
* - write buffered recv which efficiently returns string or line
*   - reads and concatenates everything available into circular buffer
*   - parses out first string or line and moves start of buffer pointer
*     to begining of next
* -----------------------------------------------------------------------
*  Wait for The next items until Students have submitted their code
* -----------------------------------------------------------------------
* - build front end, e.g., Sender and Receiver classes
* - implement message facility: message class, sendMsg and recvMsg
* - Test and Display packages
*/

#ifndef WIN32_LEAN_AND_MEAN  // prevents duplicate includes of core parts of windows.h in winsock2.h
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>      // Windnows API
#include <winsock2.h>     // Windows sockets, ver 2
#include <WS2tcpip.h>     // support for IPv6 and other things
#include <IPHlpApi.h>     // ip helpers

#include <vector>
#include <string>
#include <atomic>

#include "WindowsHelpers.h"
#include "../Utilities/Utilities.h"
#include "Logger.h"

#pragma warning(disable:4522)
#pragma comment(lib, "Ws2_32.lib")

namespace Sockets
{
	/////////////////////////////////////////////////////////////////////////////
	// SocketSystem class - manages loading and unloading Winsock library

	class SocketSystem
	{
	public:
		SocketSystem();
		~SocketSystem();
	private:
		int iResult;
		WSADATA wsaData;
	};

	/////////////////////////////////////////////////////////////////////////////
	// Socket class
	// - used by server for client handling
	// - base for SocketConnecter and SocketListener classes

	class Socket
	{
	public:
		enum IpVer { IP4, IP6 };
		using byte = char;

		// disable copy construction and assignment
		Socket(const Socket& s) = delete;
		Socket& operator=(const Socket& s) = delete;

		Socket(IpVer ipver = IP4);
		Socket(::SOCKET);
		Socket(Socket&& s);
		operator ::SOCKET() { return socket_; }
		Socket& operator=(Socket&& s);
		virtual ~Socket();

		IpVer& ipVer();
		bool send(size_t bytes, byte* buffer);
		bool recv(size_t bytes, byte* buffer);
		size_t sendStream(size_t bytes, byte* buffer);
		size_t recvStream(size_t bytes, byte* buffer);
		bool sendString(const std::string& str, byte terminator = '\0');
		std::string recvString(byte terminator = '\0');
		static std::string removeTerminator(const std::string& src);
		size_t bytesWaiting();
		bool waitForData(size_t timeToWait, size_t timeToCheck);
		bool shutDownSend();
		bool shutDownRecv();
		bool shutDown();
		void close();

		bool validState() { return socket_ != INVALID_SOCKET; }

	protected:
		WSADATA wsaData;
		::SOCKET socket_;
		struct addrinfo *result = NULL, *ptr = NULL, hints;
		int iResult;
		IpVer ipver_ = IP4;
	};

	/////////////////////////////////////////////////////////////////////////////
	// SocketConnecter class
	// - supports connecting to a SocketListener

	class SocketConnecter : public Socket
	{
	public:
		SocketConnecter(const SocketConnecter& s) = delete;
		SocketConnecter& operator=(const SocketConnecter& s) = delete;

		SocketConnecter();
		SocketConnecter(SocketConnecter&& s);
		SocketConnecter& operator=(SocketConnecter&& s);
		virtual ~SocketConnecter();

		bool connect(const std::string& ip, size_t port);
	};

	/////////////////////////////////////////////////////////////////////////////
	// SocketListener class
	// - listens for incoming connections
	// - each connection is handled on its own thread

	class SocketListener : public Socket
	{
	public:
		SocketListener(const SocketListener& s) = delete;
		SocketListener& operator=(const SocketListener& s) = delete;

		SocketListener(size_t port, IpVer ipv = IP6);
		SocketListener(SocketListener&& s);
		SocketListener& operator=(SocketListener&& s);
		virtual ~SocketListener();

		template<typename CallObj>
		bool start(CallObj& co);
		void stop();
	private:
		bool bind();
		bool listen();
		Socket accept();
		std::atomic<bool> stop_ = false;
		size_t port_;
		bool acceptFailed_ = false;
	};

	//----< SocketListener start function runs listener on its own thread >------
	/*
	*  - Accepts Callable Object that defines the operations
	*    to handle client requests.
	*  - You will find an example Callable Object, ClientProc,
	*    used in the test stub below
	*/
	template<typename CallObj>
	bool SocketListener::start(CallObj& co)
	{
		if (!bind())
		{
			return false;
		}

		if (!listen())
		{
			return false;
		}
		// listen on a dedicated thread so server's main thread won't block

		std::thread ListenThread(
			[&]()
		{
			StaticLogger<1>::write("\n  -- server waiting for connection");

			while (!acceptFailed_)
			{
				if (stop_.load())
					break;

				// Accept a client socket - blocking call

				Socket clientSocket = accept();    // uses move ctor
				if (!clientSocket.validState()) {
					continue;
				}
				StaticLogger<1>::write("\n  -- server accepted connection");

				// start thread to handle client request

				//std::thread clientThread(std::ref(co), std::move(clientSocket));
				std::thread clientThread(co, std::move(clientSocket));
				clientThread.detach();  // detach - listener won't access thread again
			}
			StaticLogger<1>::write("\n  -- Listen thread stopping");
		}
		);
		ListenThread.detach();
		return true;
	}
}
#endif

