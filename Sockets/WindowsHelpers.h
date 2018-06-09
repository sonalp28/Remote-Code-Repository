#ifndef WINDOWSHELPERS_H
#define WINDOWSHELPERS_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// WindowsHelper.h	: small helper functions for using Windows API										//
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
* This package supports programming to the Windows API.  It currently
* contains three global functions that convert strings to and from
* UTF-16, and retrieving error messages.
*
* Public interface:
* ------------------
* std::string WindowsHelpers::wstringToString(const std::wstring& wstr) - converts given wide string to string & returns it
* std::wstring WindowsHelpers::stringToWideString(const std::string& str) - converts given string to wide string & returns it
* std::string WindowsHelpers::GetLastMsg(bool WantSocketMsg) - get socket error message string
* 
* Build Process:
* --------------
* Required Files: WindowsHelper.h, WindowwsHelper.cpp
*
* Build Command: devenv WindowsHelper.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 22 Feb 2016
* - first release
*
*/

#include <string>
#include <vector>

namespace WindowsHelpers
{
	std::string wstringToString(const std::wstring& wstr);
	std::wstring stringToWideString(const std::string& str);
	std::string GetLastMsg(bool wantSocketMessage);
}

#endif
