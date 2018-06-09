#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// checkin.h			: demonstrate check-in package operations											//
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
* This package defines class checkin which checks in the files given by user into repository
*
* Public Interface:
* =================
* checkin(std::string s, std::string d) : file1(s), file2(d) {} - parameterized constructor with initilization list to initialize private params of class
* bool checkinFile() - memeber function of check-in class to copy files from source to destination using File class defined in FileSystem.h
*
* Required Files:
* ===============
* checkin.h, checkin.cpp
* FileSystem.h, FileSystem.cpp
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
#include "../FileSystem/FileSystem.h"

using namespace FileSystem;

namespace CheckIn
{
	/////////////////////
	//Check-in class
	/////////////////////
	class checkin {
	public:
		checkin(std::string s, std::string d) : file1(s), file2(d) {}		//parameterized constructor
		bool checkinFile();												//function implemented in cpp file

	private:
		std::string file1;
		std::string file2;
	};

}
