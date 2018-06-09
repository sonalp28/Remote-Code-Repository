#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// version.h			: demonstrate version package operations											//
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
#include <string>

namespace Version
{
	/////////////////////
	//version class
	/////////////////////
	class version {
	public:
		version(std::string str) :s(str) { }							//parameterized constructor
		std::string giveVersion(std::string str, int count);		//function implemented in cpp file
		std::string removeVersion();								//function implemented in cpp file
	private:
		std::string s;
	};
}