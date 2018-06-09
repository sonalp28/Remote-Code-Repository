//////////////////////////////////////////////////////////////////////////////////////////////////////////
// CommLibWrapper.cpp: Comm object factory															    //
// ver 1.0			 																					//
// Platform          : Dell Inspiron 13 - Windows 10, Visual Studio 2017                                //-|_ 
// Language          : C++ using the facilities of the standard C++ Libraries                           //-|  <----------Requirement 1---------->
// Application      : Project 4 [Remote Code Repository] Object Oriented Design CSE-687 Spring'18		//
// Author            : Dr. Jim Fawcett, EECS, SU                                                        // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*  Package operation -
* ---------------------
*  Provides export and import declarations for Comm
*
*  Public interface -
* --------------------
*  DLL_DECL IComm* CommFactory::create(const std::string& machineAddress, size_t port) - function using CommFactory to invoke IComm::create
*
*  Required Files:
* -----------------
*  CommLibWrapper.h, CommLibWrapper.cpp
*
*  Build Command:
* ----------------
*  devenv repo.sln /rebuild debug
*
*  Maintenance History:
* ----------------------
*  ver 1.0 : 27 Mar 2018
*  - first release
*/

#define IN_DLL

#include "CommLibWrapper.h"
#include "../Comm/Comm.h"  // definition of create

using namespace MsgPassingCommunication;

/*<----------------------- function using CommFactory to invoke IComm::create ----------------------------->*/
DLL_DECL IComm* CommFactory::create(const std::string& machineAddress, size_t port)
{
	//std::cout << "\n  using CommFactory to invoke IComm::create";
	return IComm::create(machineAddress, port);
}


