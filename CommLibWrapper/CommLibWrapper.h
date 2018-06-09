#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// CommLibWrapper.h : Comm object factory															    //
// ver 1.0																								//
// Platform         : Dell Inspiron 13 - Windows 10, Visual Studio 2017                                 //-|_ 
// Language         : C++ using the facilities of the standard C++ Libraries                            //-|  <----------Requirement 1---------->
// Application      : Project 4 [Remote Code Repository] Object Oriented Design CSE-687 Spring'18		//
// Author           : Dr. Jim Fawcett, EECS, SU                                                         // 
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
#include <string>
#include "../Comm/IComm.h"

#ifdef IN_DLL
#define DLL_DECL __declspec(dllexport)
#else
#define DLL_DECL __declspec(dllimport)
#endif

namespace MsgPassingCommunication
{
	extern "C" {
		struct CommFactory {
			static DLL_DECL IComm* create(const std::string& machineAddress, size_t port);
		};
	}
}