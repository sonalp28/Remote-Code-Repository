//////////////////////////////////////////////////////////////////////////////////////////////////////////
// WindowsHelper.cpp : small helper functions for using Windows API										//
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

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <string>
#include <winsock2.h>
#include "WindowsHelpers.h"

using namespace WindowsHelpers;

#pragma comment(lib, "Ws2_32.lib")

//-----< converts given wide string to string & returns it ----------------
std::string WindowsHelpers::wstringToString(const std::wstring& wstr)
{
	std::string rtn;
	for (auto ch : wstr)
		rtn += static_cast<char>(ch);
	rtn += '\0';
	return rtn;
}

//-----< converts given string to wide string & returns it ----------------
std::wstring WindowsHelpers::stringToWideString(const std::string& str)
{
	std::wstring rtn;
	for (auto ch : str)
		rtn += ch;
	rtn += static_cast<wchar_t>('\0');
	return rtn;
}

//----< get socket error message string >----------------------------
std::string WindowsHelpers::GetLastMsg(bool WantSocketMsg) {

	// ask system what type of error occurred

	DWORD errorCode;
	if (WantSocketMsg)
		errorCode = WSAGetLastError();
	else
		errorCode = GetLastError();
	if (errorCode == 0)
		return "no error";

	// map errorCode into a system defined error string

	DWORD dwFlags =
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER;
	LPCVOID lpSource = NULL;
	DWORD dwMessageID = errorCode;
	DWORD dwLanguageId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
	LPSTR lpBuffer;
	DWORD nSize = 0;
	va_list *Arguments = NULL;

	FormatMessage(
		dwFlags, lpSource, dwMessageID, dwLanguageId,
		(LPTSTR)&lpBuffer, nSize, Arguments
	);

	std::string _msg(lpBuffer);
	LocalFree(lpBuffer);
	return _msg;
}

/*<------------------------------ test stub ---------------------------------->*/
#ifdef TEST_WINDOWSHELPERS

int main()
{

}

#endif
