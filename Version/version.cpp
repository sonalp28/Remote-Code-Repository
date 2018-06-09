//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// version.cpp			: demonstrate version package operations											//
// ver 1.0																								    //
// Platform             : Dell Inspiron 13 - Windows 10, Visual Studio 2017                                 //-|_ 
// Language             : C# & .Net Framework                                                               //-|  <----------Requirement 1---------->
// Application          : Project 4 [Remote Code Repository] Object Oriented Design CSE-687 Spring'18       //
// Author               : Sonal Patil, Syracuse University                                                  //
//                        spatil06@syr.edu (408)-416-6291                                                   // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
* This package defines class version which provides means to manage version numbering for all files held in the Repository
*
* Public Interface:
* =================
* version(std::string str):s(str) - a string on which append version & remove version will get performed id passed to this constructor
* std::string giveVersion(std::string str, int count) - function to append version into current file name
* std::string removeVersion() - function to remove version from given file name
*
* Required Files:
* ===============
* version.h, version.cpp
*
* Build Command:
* ==============
*
*
* Maintenance History:
* ====================
* ver 1.0 : 06 March 18
* - first release
*/

#include <iostream>
#include "version.h"


/*<---------------------------------------function to append version into current file name--------------------------------------------------->*/
std::string Version::version::giveVersion(std::string str, int count)
{
	std::string version_str = "";
	version_str = "." + std::to_string(count);
	str += version_str;
	return str;
}

/*<-----------------------------------------function to remove version from given file name--------------------------------------------------->*/
std::string Version::version::removeVersion()
{
	std::size_t found = s.find_last_of("/\\");
	std::string str = s.substr(found + 1, s.size());
	std::cout << "     File name after removing version information : " << str.substr(0, str.size() - 2) << "\n";
	return s.substr(0, s.size() - 2);
}

/*<-------------------------------------test stub---------------------------------------->*/
#ifdef TEST_VERSION
int main() {
	std::cout << "Version package test stub";
	Version::version v("display.h");
	std::string return_str = v.giveVersion("display.h", 1);
	std::cout << return_str;
	return 1;
}
#endif // TEST_VERSION



